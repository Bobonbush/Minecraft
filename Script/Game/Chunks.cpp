#include "Chunks.h"


void Frustum::normalize(glm::vec4 & plane) {
    float distance = glm::length(glm::vec3(plane));
    plane /= distance;
    return ;
}

void Frustum::update() {
    Player * player = Player::getInstance();
        Setting * settings = Setting::getInstance();
        glm::mat4 view = player -> getViewMatrix();
        glm::mat4 projection = player -> getProjectionMatrix(settings -> getResolution().x , settings -> getResolution().y);
        glm::mat4 viewProjMatrix =  projection * view ;
        
        planes[0].x = viewProjMatrix[0][3] + viewProjMatrix[0][0];
        planes[0].y = viewProjMatrix[1][3] + viewProjMatrix[1][0];
        planes[0].z = viewProjMatrix[2][3] + viewProjMatrix[2][0];
        planes[0].w = viewProjMatrix[3][3] + viewProjMatrix[3][0];

        normalize(planes[0]);
        //std::cout << "Right : " << planes[0].x << ", " << planes[0].y << ", " << planes[0].z << ", " << planes[0].w  << '\n';

       



        planes[1].x = viewProjMatrix[0][3] - viewProjMatrix[0][0];
        planes[1].y = viewProjMatrix[1][3] - viewProjMatrix[1][0];
        planes[1].z = viewProjMatrix[2][3] - viewProjMatrix[2][0];
        planes[1].w = viewProjMatrix[3][3] - viewProjMatrix[3][0];
        normalize(planes[1]);

        
        

        //std::cout << "Left : " << planes[1].x << ", " << planes[1].y << ", " << planes[1].z<< ", " << planes[1].w  << '\n';
        
        planes[2].x = viewProjMatrix[0][3] - viewProjMatrix[0][1];
        planes[2].y = viewProjMatrix[1][3] - viewProjMatrix[1][1];
        planes[2].z = viewProjMatrix[2][3] - viewProjMatrix[2][1];
        planes[2].w = viewProjMatrix[3][3] - viewProjMatrix[3][1];
        normalize(planes[2]);

        

       // std::cout << "Bottom : " << planes[2].x << ", " << planes[2].y << ", " << planes[2].z<< ", " << planes[2].w <<  '\n';
        
        planes[3].x = viewProjMatrix[0][3] + viewProjMatrix[0][1];
        planes[3].y = viewProjMatrix[1][3] + viewProjMatrix[1][1];
        planes[3].z = viewProjMatrix[2][3] + viewProjMatrix[2][1];
        planes[3].w = viewProjMatrix[3][3] + viewProjMatrix[3][1];
        normalize(planes[3]);

    
        
        

        //std::cout << "Top : " << planes[3].x << ", " << planes[3].y << ", " << planes[3].z<< ", " << planes[3].w <<  '\n';
        
        planes[4].x = viewProjMatrix[0][3] + viewProjMatrix[0][2];
        planes[4].y = viewProjMatrix[1][3] + viewProjMatrix[1][2];
        planes[4].z = viewProjMatrix[2][3] + viewProjMatrix[2][2];
        planes[4].w = viewProjMatrix[3][3] + viewProjMatrix[3][2];
        normalize(planes[4]);
        
        

        //std::cout << "Near : " << planes[4].x << ", " << planes[4].y << ", " << planes[4].z << "," << planes[4].w << '\n';
        
        planes[5].x = viewProjMatrix[0][3] - viewProjMatrix[0][2];
        planes[5].y = viewProjMatrix[1][3] - viewProjMatrix[1][2];
        planes[5].z = viewProjMatrix[2][3] - viewProjMatrix[2][2];
        planes[5].w = viewProjMatrix[3][3] - viewProjMatrix[3][2];
        normalize(planes[5]);

        //std::cout << "Far : " << planes[5].x << ", " << planes[5].y << ", " << planes[5].z << ", " << planes[5].w << '\n';
        
}

const bool Frustum::isChunkInFrustum(const glm::vec3 & origin, float chunkSize){
            glm::vec3 min = origin - glm::vec3(chunkSize /2.f) ;
            glm::vec3 max = origin + glm::vec3(chunkSize /2.f) ;
            max.y += chunkSize / 2.f;
            min.y += chunkSize / 2.f;
            
            for(int i = 0; i < 6 ; i++) {
                int out = 0;
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, min.z, 1.f))  < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                if(out == 8) {
                    return false;
                }
            }
            /*
            int out = 0;
            
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x > max.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x < min.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y > max.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y < min.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z > max.z)? 1 : 0); if(out == 8) return false;

            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z < min.z)? 1 : 0); if(out == 8) return false;
            */
            
            return true;
        }

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
        blocks.push_back(std::make_shared<Stone>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f), shader));
    }

    if(blockType == BlockType::WATER) {
        blocks.push_back(std::make_shared<Water>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f), shader));
    }
}


void SubChunk::Culling() {
    Setting * settings = Setting::getInstance();
    CompleteRender = true;

    for(int x = 0 ; x < settings -> getChunkSize().x && CompleteRender ; x++ ) {
        for(int z = 0 ; z < settings -> getChunkSize().z && CompleteRender ; z++) {
            for(int y = 0 ; y < settings -> getSubChunkResolution().y && CompleteRender ; y++) {
                

                if(LoadedBlocks[x][y][z]) {
                    continue;
                }

                if(!settings -> BlockLoad()) {
                    CompleteRender = false;
                    iterator = glm::vec3(x, z, y);
                    continue;
                }

                


                LoadedBlocks[x][y][z] = true;

                if(BlockMap[x][y][z] == BlockType::AIR) {
                    continue;
                }
                glm::vec3 position = BlockPosMap[x][y][z];
                bool Left = false;
                bool Right = false;
                bool Top = false;
                bool Bottom = false;
                bool Front = false;
                bool Back = false;
                
                if(settings ->  getBlockMap(glm::vec3 (position.x - settings -> getBlockNDCSize().x, position.y, position.z)) == true) {
                    Left = true;
                }
                if(settings ->  getBlockMap(glm::vec3 (position.x + settings -> getBlockNDCSize().x, position.y, position.z)) == true) {
                    Right = true;
                }

                if(settings ->  getBlockMap(glm::vec3 (position.x, position.y + settings -> getBlockNDCSize().y, position.z)) == true) {
                    Top = true;
                }

                if(settings ->  getBlockMap(glm::vec3 (position.x, position.y - settings -> getBlockNDCSize().y, position.z)) == true) {
                    Bottom = true;
                }

                if(settings ->  getBlockMap(glm::vec3 (position.x, position.y, position.z + settings -> getBlockNDCSize().z)) == true) {
                    Back = true;
                }

                if(settings ->  getBlockMap(glm::vec3 (position.x, position.y, position.z - settings -> getBlockNDCSize().z)) == true) {
                    Front = true;
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
    if(CompleteRender || !ChunkLoaded) {
        return;
    }
    Culling();
}

void SubChunk::Update(float deltaTime) {
    
    std::vector<std::shared_ptr<Rigidbody>> validBodies;         // FOr physics detection
    int i = 0 ;
    LoadBlock();
    for (auto &block : blocks) {
        block -> PrepareRender(banFace[i]);                         // Set valid positions 
        i++;
    }

    

    for(auto &block : blocks) {
        block -> Update(deltaTime);
    }
}

std::vector<std::shared_ptr<Rigidbody>> SubChunk::LoadRigidBody() {
    std::vector<std::shared_ptr<Rigidbody>> validBodies;
    for(auto &block : blocks) {
        validBodies.push_back(block -> rigidbody);
    }
    return validBodies;
}


void SubChunk::LoadChunk() {
    if(ChunkLoaded) {
        return;
    }
    if(firstLoad) {
        GenerateChunk();
        firstLoad = false;
    }

    ChunkLoaded = true;

    for(int x = 0; x < settings -> getChunkSize().x && ChunkLoaded ; x++ ) {
        for(int z = 0; z < settings -> getChunkSize().z && ChunkLoaded ; z++) {
            for(int y = 0 ; y < settings -> getSubChunkResolution().y && ChunkLoaded ; y++) {

                
                if(LoadedBlocks[x][y][z]) {
                    continue;
                }
                if(!settings -> BlockLoad()) {
                    ChunkLoaded = false;
                    iterator = glm::vec3(x, z, y);
                    break;
                }

                LoadedBlocks[x][y][z] = true;
                
                
                

                glm::vec3 position = origin;
                position.x += x * settings -> getBlockNDCSize().x;
                position.z += z * settings -> getBlockNDCSize().z;
                position.y += y * settings -> getBlockNDCSize().y;
                position.x -= settings -> getBlockNDCSize().x * (settings -> getChunkSize().x - 1) /2.f;
                position.z -= settings -> getBlockNDCSize().z * (settings -> getChunkSize().z - 1) /2.f;
                BlockType blockType = GetBlockState(position.x, position.y, position.z);
                BlockMap[x][y][z] = blockType;

                if(blockType != BlockType::AIR) {
                    settings -> setBlockMap(position, true);
                }
                BlockPosMap[x][y][z] = position;
            }
        }
    }

    if(ChunkLoaded) {
        iterator = glm::vec3(0.f);
        for(int x = 0 ; x < settings -> getChunkSize().x ; x++) {
            for(int z = 0 ; z < settings -> getChunkSize().z ; z++) {
                for(int y = 0 ; y < settings -> getSubChunkResolution().y ; y++) {
                    LoadedBlocks[x][y][z] = false;
                }
            }
        }
    }
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
}




void SubChunk::ReloadChunk() {
    //Culling();
}

// Chunk implementation

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

        
        if( (int) subChunks.size() > i) {
            subChunks[i] -> LoadChunk();
            continue;
        }
        subChunks.push_back(std::make_shared<SubChunk>(origin + glm::vec3(0.f, i * settings -> getSubChunkResolution().y * settings -> getBlockNDCSize().y, 0.f)));
        subChunks.back() -> LoadChunk();
        break;
    }
}

void Chunk::Render(glm::mat4 view, glm::mat4 projection) {
    for(auto &subChunk : RenderSubChunks) {
        subChunk -> Render(view, projection);
    }
}



void Chunk::Update(float deltaTime, glm::vec3 playerPosition, float diameter, glm::mat4 ProjView) {
    RenderSubChunks.clear();

    Frustum frustum;
    frustum.update();

    std::sort(subChunks.begin(), subChunks.end(), [&playerPosition](std::shared_ptr<SubChunk> a, std::shared_ptr<SubChunk> b) {
        return glm::length(a -> GetOrigin() - playerPosition) < glm::length(b -> GetOrigin() - playerPosition);
    });
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
    

    for(auto &subChunk : subChunks) {
        float offset = 0.5f;
        if(glm::length(subChunk -> GetOrigin() - playerPosition) > diameter * settings -> getBlockNDCSize().x * settings -> getChunkSize().x * offset) {
           // continue;
        }
        if(frustum.isChunkInFrustum(subChunk -> GetOrigin(), settings -> getChunkSize().x * settings -> getBlockNDCSize().x )) {
            RenderSubChunks.push_back(subChunk);
            
        }else continue;

        subChunk -> Update(deltaTime);
    }

}

std::vector<std::shared_ptr<Rigidbody>> Chunk::LoadRigidBody() {
    std::vector<std::shared_ptr<Rigidbody>> validBodies;
    for(auto &subChunk : subChunks) {
        for(auto &body : subChunk -> LoadRigidBody()) {
            validBodies.push_back(body);
        }
    }

    return validBodies;
} 

std::vector<std::shared_ptr<Block>> Chunk::GetBlocks() {
    std::vector<std::shared_ptr<Block>> blocks;
    for(auto &subChunk : subChunks) {
        for(auto &block : subChunk -> GetBlocks()) {
            blocks.push_back(block);
        }
    }
    return blocks;
}

void Chunk::ReloadChunk() {
    for(auto &subChunk : subChunks) {
        subChunk -> ReloadChunk();
    }
}