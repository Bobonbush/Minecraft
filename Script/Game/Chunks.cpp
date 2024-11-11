#include "Chunks.h"



SubChunk::BlockType SubChunk::GetBlockState(float x, float y, float z) {
    GroundSelector groundSelector;
    Setting * settings = Setting::getInstance();
    if(groundSelector.isGround(x, y, z)) {
        return BlockType::STONE;
    }

    if(y < settings -> getSurfaceLevel()) {
        return BlockType::WATER;
    }
    return BlockType::AIR;
}
/*
Task : Remove the blocks that are not visible to the player

Solution : 

1. Create a frustum object from the player's view and extract the planes
2. For each block in the chunk, check if the block is visible to the player
3. If the block is visible, add it to the validBodies vector
*/

void SubChunk::AddBlock(BlockType blockType, glm::vec3 position) {
    ShaderManager * shaderManager = ShaderManager::getInstance();
    Setting * settings = Setting::getInstance();
    std::shared_ptr<Shader> shader = shaderManager -> GetShader("block");

    if(blockType == BlockType::AIR) {
        return;
    }
    if(blockType == BlockType::STONE) {
        blocks.push_back(std::make_unique<Stone>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f), shader));
    }

    if(blockType == BlockType::WATER) {
        blocks.push_back(std::make_unique<Water>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f), shader));
    }
}
void SubChunk::Culling() {
    Setting * settings = Setting::getInstance();
    CompleteRender = true;

    for(int x = 0 ; x < settings -> getChunkSize().x && CompleteRender ; x++ ) {
        for(int z = 0 ; z < settings -> getChunkSize().z && CompleteRender ; z++) {
            for(int y = 0 ; y < settings -> getSubChunkResolution().y && CompleteRender ; y++) {
                if(BlockMap[x][y][z] == BlockType::AIR) {
                    continue;
                }

                if(LoadedBlocks[x][y][z]) {
                    continue;
                }

                if(!settings -> BlockLoad()) {
                    CompleteRender = false;
                    continue;
                }


                LoadedBlocks[x][y][z] = true;
                glm::vec3 position = BlockPosMap[x][y][z];
                bool Left = false;
                bool Right = false;
                bool Top = false;
                bool Bottom = false;
                bool Front = false;
                bool Back = false;
                
                if(x > 0 &&  BlockMap[x-1][y][z] != AIR) {
                    Left = true;
                }
                if(x + 1 < settings -> getChunkSize().x && BlockMap[x+1][y][z] != AIR) {
                    Right = true;
                }
                if(y > 0 &&  BlockMap[x][y-1][z] != AIR) {
                    Bottom = true;
                }

                if(y + 1 <  settings -> getSubChunkResolution().y && BlockMap[x][y+1][z] != AIR) {
                    Top = true;
                }

                if(z > 0 && BlockMap[x][y][z-1] != AIR) {
                    Front = true;
                }

                if(z + 1 < settings -> getChunkSize().z && BlockMap[x][y][z+1] != AIR) {
                    Back = true;
                }

                if(Left && Right && Top && Bottom && Front && Back) {
                    continue;
                }
                int mask = (Top << 0) | (Bottom << 1) | (Left << 2) | (Right << 3) | (Back << 4) | (Front << 5);
                
                AddBlock(BlockMap[x][y][z], position);
                banFace.push_back(mask);
            }
        }
    }
 }


SubChunk::SubChunk(glm::vec3 origin) {
    this->origin = origin;
    settings = Setting::getInstance();
    shaderManager = ShaderManager::getInstance();
    player = Player::getInstance();
} 

SubChunk::~SubChunk() {
}

void SubChunk::Render(glm::mat4 view, glm::mat4 projection) {
    for (auto &block : blocks) {
        block -> Render(view, projection);
    }
}

void SubChunk::LoadBlock() {
    if(CompleteRender) {
        return;
    }
    Culling();
}

std::vector<std::shared_ptr<Rigidbody>> SubChunk::Update(float deltaTime) {
    
    std::vector<std::shared_ptr<Rigidbody>> validBodies;         // FOr physics detection
    int i = 0 ;
    LoadBlock();
    for (auto &block : blocks) {
        block -> PrepareRender(banFace[i]);                         // Set valid positions 
        i++;
        validBodies.push_back(block -> rigidbody);
    }

    

    for(auto &block : blocks) {
        block -> Update(deltaTime);
    }
    return validBodies;
}


void SubChunk::LoadChunk() {
    GenerateChunk();
}

void SubChunk::GenerateChunk() {
    Setting * settings = Setting::getInstance(); 
    ShaderManager * shaderManager = ShaderManager::getInstance();
    int chunkSizeX = settings -> getChunkSize().x;
    int chunkHeight = settings -> getSubChunkResolution().y;
    int chunkSizeZ = settings -> getChunkSize().z;
    BlockMap.resize(chunkSizeX);
    BlockPosMap.resize(chunkSizeX);
    LoadedBlocks.resize(chunkSizeX);

    for(int i = 0 ; i < chunkSizeX ; i++) {
        BlockMap[i].resize(chunkHeight);
        BlockPosMap[i].resize(chunkHeight);
        LoadedBlocks[i].resize(chunkHeight);
        for(int j = 0 ; j < chunkHeight ; j++) {
            BlockMap[i][j].resize(chunkSizeZ);
            BlockPosMap[i][j].resize(chunkSizeZ);
            LoadedBlocks[i][j].resize(chunkSizeZ);
        }
    }


    for(int x = 0 ; x < settings -> getChunkSize().x ; x++ ) {
        for(int z = 0 ; z < settings -> getChunkSize().z ; z++) {
            for(int y = 0 ; y < settings -> getSubChunkResolution().y ; y++) {
                glm::vec3 position = origin;
                position.x += x * settings -> getBlockNDCSize().x;
                position.z += z * settings -> getBlockNDCSize().z;
                position.y += y * settings -> getBlockNDCSize().y;
                position.x -= settings -> getBlockNDCSize().x * (settings -> getChunkSize().x - 1) /2.f;
                position.z -= settings -> getBlockNDCSize().z * (settings -> getChunkSize().z - 1) /2.f;
                BlockType blockType = GetBlockState(position.x, position.y, position.z);
                BlockMap[x][y][z] = blockType;

                BlockPosMap[x][y][z] = position;
            }
        }
    }
}



Chunk::Chunk(glm::vec3 origin) : origin(origin) {

}

Chunk::~Chunk() {
}

void Chunk::LoadChunk() {
    Setting * settings = Setting::getInstance();
    ShaderManager * shaderManager = ShaderManager::getInstance();
    int chunkSizeX = settings -> getChunkSize().x;
    int chunkHeight = settings -> getChunkSize().y / settings -> getSubChunkResolution().y;
    int chunkSizeZ = settings -> getChunkSize().z;


    

    for(int i = 0 ; i < chunkHeight ; i++) {
        subChunks.push_back(std::make_shared<SubChunk>(origin + glm::vec3(0.f, i * settings -> getSubChunkResolution().y, 0.f)));
        subChunks.back() -> LoadChunk();
    }
}

void Chunk::Render(glm::mat4 view, glm::mat4 projection) {
    for(auto &subChunk : RenderSubChunks) {
        subChunk -> Render(view, projection);
    }
}

std::vector<std::shared_ptr<Rigidbody>> Chunk::Update(float deltaTime, glm::vec3 playerPosition, float diameter, glm::mat4 ProjView) {
    std::vector<std::shared_ptr<Rigidbody>> validBodies;
    RenderSubChunks.clear();

    Frustum frustum;
    frustum.update();
    /*

    std::cout << "Frustum :" <<'\n';

    std::cout << "Top Left : " << frustum.planes[0].x << " " << frustum.planes[0].y << " " << frustum.planes[0].z << " " << frustum.planes[0].w << '\n';
    std::cout << "Top Right : " << frustum.planes[1].x << " " << frustum.planes[1].y << " " << frustum.planes[1].z << " " << frustum.planes[1].w << '\n';
    std::cout << "Bottom Left : " << frustum.planes[2].x << " " << frustum.planes[2].y << " " << frustum.planes[2].z << " " << frustum.planes[2].w << '\n';
    std::cout << "Bottom Right : " << frustum.planes[3].x << " " << frustum.planes[3].y << " " << frustum.planes[3].z << " " << frustum.planes[3].w << '\n';
    std::cout << "Near : " << frustum.planes[4].x << " " << frustum.planes[4].y << " " << frustum.planes[4].z << " " << frustum.planes[4].w << '\n';
    std::cout << "Far : " << frustum.planes[5].x << " " << frustum.planes[5].y << " " << frustum.planes[5].z << " " << frustum.planes[5].w << '\n';
*/
    Setting * settings = Setting::getInstance();
    glm::vec2 quadTreePosition(0.f, 0.f);
    glm::vec2 quadTreeSize(settings -> getResolution().x, settings -> getResolution().y);

    QuadTreeNode quadTree(quadTreePosition, quadTreeSize, 0);
    

    for(auto &subChunk : subChunks) {
        
        if(!(glm::distance(subChunk -> GetOrigin(), playerPosition) <= diameter)  ) {
            //continue;
        }
        

        if(frustum.isChunkInFrustum(subChunk -> GetOrigin(), settings -> getChunkSize().x * settings -> getBlockNDCSize().x )) {
            RenderSubChunks.push_back(subChunk);
        }else continue;

        

        
        std::vector<std::shared_ptr<Rigidbody>> subValidBodies = subChunk -> Update(deltaTime);
        for(auto &body : subValidBodies) {
            validBodies.push_back(body);
        }
    }

    return validBodies;
}