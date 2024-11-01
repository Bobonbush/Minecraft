#include "Chunks.h"



Chunk::BlockType Chunk::GetBlockState(float x, float y, float z) {
    //float noise = db::perlin(x / 128.0, y /128.0, z/128.0) * 1.00 + db::perlin(x / 32.0, y /32.0, z/32.0) * 0.5 + db::perlin(x / 16.0 , y /16.0, z/16.0) * 0.25 + db::perlin(x/8.0, y/ 8.0, z/8.0) * 0.125; // 4 octaves
    float noise = db::perlin(x / 16.0, y / 16.0, z / 16.0) * 6.5f // Base level, medium scale
            + db::perlin(x / 64.0, y / 64.0, z / 64.0) * 4.0f  // Low frequency, high amplitude for mountains
            + db::perlin(x / 4.0, y / 4.0, z / 4.0) * 3.5f  // High frequency, low amplitude for detail
            + db::perlin(x / 128 , y / 128 , z /128) * 3.f;    

    noise = pow(noise , 0.05f);
    Setting * settings = Setting::getInstance();
    float surface = settings -> getSurfaceLevel();
    

    if(y <= SPA::max(surface + noise * 50, -1.f)) {
        return BlockType::STONE;
    }

    if(y <= surface) {
        return BlockType::WATER;
    }



    return BlockType::AIR;
}

void Chunk::SoftNoise(std::vector<std::vector<float>> &elavationMap) {
     int n = (int)elavationMap.size();
     for (int i = 0; i < n; i++) {
         int m = (int)elavationMap[i].size();
         for (int j = 0; j < m; j++) {
             if(i + 1 < n )
                 elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i+1][j] );
             if(j + 1 < m)
                 elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i][j+1] );
             if(i + 1 < n && j + 1 < m)
                 elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i+1][j+1] );
         }
     }
 }

 void Chunk::HardNoise(std::vector<std::vector<float>> &elavationMap) {
     int n = (int)elavationMap.size();
     for (int i = 0; i < n; i++) {
         int m = (int)elavationMap[i].size();
         for (int j = 0; j < m; j++) {
             if(i + 1 < n )
                 elavationMap[i][j] = SPA::max(elavationMap[i][j] , elavationMap[i+1][j] );
             if(j + 1 < m)
                 elavationMap[i][j] = SPA::max(elavationMap[i][j] , elavationMap[i][j+1] );
             if(i + 1 < n && j + 1 < m)
                 elavationMap[i][j] = SPA::max(elavationMap[i][j] , elavationMap[i+1][j+1] );
         }
     }
 }

 void Chunk::SoftHeight(std::vector<std::vector<int>> & HeightMap) {
     int n = (int)HeightMap.size();
     for (int i = 0; i < n; i++) {
         int m = (int)HeightMap[i].size();
         for (int j = 0; j < m; j++) {
             if(i + 1 < n )
                 HeightMap[i][j] = SPA::min(HeightMap[i][j] , HeightMap[i+1][j] );
             if(j + 1 < m)
                 HeightMap[i][j] = SPA::min(HeightMap[i][j] , HeightMap[i][j+1] );
             if(i + 1 < n && j + 1 < m)
                 HeightMap[i][j] = SPA::min(HeightMap[i][j] , HeightMap[i+1][j+1] );
         }
     }
 }

 void Chunk::HardHeight(std::vector<std::vector<int>> & HeightMap) {
     int n = (int)HeightMap.size();
     for (int i = 0; i < n; i++) {
         int m = (int)HeightMap[i].size();
         for (int j = 0; j < m; j++) {
             if(i + 1 < n )
                 HeightMap[i][j] = SPA::max(HeightMap[i][j] , HeightMap[i+1][j] );
             if(j + 1 < m)
                 HeightMap[i][j] = SPA::max(HeightMap[i][j] , HeightMap[i][j+1] );
             if(i + 1 < n && j + 1 < m)
                 HeightMap[i][j] = SPA::max(HeightMap[i][j] , HeightMap[i+1][j+1] );
         }
     }
 }

/*
Task : Remove the blocks that are not visible to the player

Solution : 

1. Create a frustum object from the player's view and extract the planes
2. For each block in the chunk, check if the block is visible to the player
3. If the block is visible, add it to the validBodies vector
*/

void Chunk::AddBlock(BlockType blockType, glm::vec3 position) {
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
void Chunk::Culling() {
    Setting * settings = Setting::getInstance();
    
    blocks.clear();
    for(int x = 0 ; x < settings -> getChunkSize().x ; x++ ) {
        for(int z = 0 ; z < settings -> getChunkSize().z ; z++) {
            for(int y = 0 ; y < settings -> getChunkSize().y ; y++) {
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
                
                if(x > 0 &&  BlockMap[x-1][y][z] != AIR) {
                    Left = true;
                }
                if(x + 1 < settings -> getChunkSize().x && BlockMap[x+1][y][z] != AIR) {
                    Right = true;
                }
                if(y > 0 &&  BlockMap[x][y-1][z] != AIR) {
                    Bottom = true;
                }

                if(y + 1 <  settings -> getChunkSize().y && BlockMap[x][y+1][z] != AIR) {
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


Chunk::Chunk(glm::vec3 origin) {
    this->origin = origin;
    settings = Setting::getInstance();
    shaderManager = ShaderManager::getInstance();
    player = Player::getInstance();
} 

Chunk::~Chunk() {
}

void Chunk::Render(glm::mat4 view, glm::mat4 projection) {
    for (auto &block : blocks) {
        block -> Render(view, projection);
    }
}

std::vector<std::shared_ptr<Rigidbody>> Chunk::Update(float deltaTime) {

    std::vector<std::shared_ptr<Rigidbody>> validBodies;         // FOr physics detection
    Frustum frustum = player -> extractFrustumPlanes();
    int i = 0 ;
    for (auto &block : blocks) {
        block -> PrepareRender(frustum, banFace[i]);                         // Set valid positions 
        i++;
        validBodies.push_back(block -> rigidbody);
    }

    for(auto &block : blocks) {
        block -> Update(deltaTime);
    }
    return validBodies;
}


void Chunk::LoadChunk() {
    GenerateChunk();
}

void Chunk::GenerateChunk() {
    Setting * settings = Setting::getInstance(); 
    ShaderManager * shaderManager = ShaderManager::getInstance();
    int chunkSizeX = settings -> getChunkSize().x;
    int chunkHeight = settings -> getChunkSize().y;
    int chunkSizeZ = settings -> getChunkSize().z;
    BlockMap.resize(chunkSizeX);
    BlockPosMap.resize(chunkSizeX);
    for(int i = 0 ; i < chunkSizeX ; i++) {
        BlockMap[i].resize(chunkHeight);
        BlockPosMap[i].resize(chunkHeight);
        for(int j = 0 ; j < chunkHeight ; j++) {
            BlockMap[i][j].resize(chunkSizeZ);
            BlockPosMap[i][j].resize(chunkSizeZ);
        }
    }


    for(int x = 0 ; x < settings -> getChunkSize().x ; x++ ) {
        for(int z = 0 ; z < settings -> getChunkSize().z ; z++) {
            for(int y = 0 ; y < settings -> getChunkSize().y ; y++) {
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

    Culling();

}