#include "Chunks.h"



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

    std::vector<std::shared_ptr<Rigidbody>> validBodies;
    Frustum frustum = player -> extractFrustumPlanes();
    for (auto &block : blocks) {
        block -> PrepareRender(frustum);
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
    int width = settings -> getChunkSize().x;
    int height = settings -> getChunkSize().y;
    
         
    std::vector<std::vector<float>> elavationMap(width, std::vector<float>(height, 0));
    std::vector<std::vector<float>> temperatureMap(width, std::vector<float>(height, 0));

    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float nx = i;
            float ny = j;

            elavationMap[i][j] = db::perlin(nx / 64.f, ny / 64.f ) * 1.00f + db::perlin(nx / 32.f, ny / 32.f ) * 0.5f + db::perlin(nx / 16.f, ny / 16.f ) * 0.25f;
            
        }
    }

    for(int i = 0 ; i < width ; i++) {
        for(int j = 0 ; j < height ;j ++) {
            elavationMap[i][j] = (elavationMap[i][j] + 1.f) / 2.f ;
            elavationMap[i][j] = pow(elavationMap[i][j], 4.f);
            //SPA::clamp(elavationMap[i][j], 0.f, 1.f);
            //std::cout << elavationMap[i][j] << " ";
        }
        //std::cout << std::endl;
    }

    std::vector<std::vector<int>> HeightMap(width, std::vector<int>(height, 0));


    SoftNoise(elavationMap);
    HardNoise(elavationMap);
    for(int i = 0 ; i < width ; i++) {
        for(int j = 0 ; j < height ;j ++) {
            float e = elavationMap[i][j];
            int blockHeight = 0;
            int blockType = 0;
            if(e < 0.02f) {          // Water Level
                blockHeight = 1;
                blockType = WATER;
            }else if(e < 0.03f) {    // Sand Level
                blockHeight = SPA::RandomInt(1, 2);
                blockType = SAND;
            } else if(e < 0.4f) {   // Dirt Level
                blockHeight = SPA::RandomInt(2, 4);

                blockType = DIRT;
            } else {                // Stone Level
                blockHeight = SPA::RandomInt(10, 45); 

                blockType = STONE;
            }

            HeightMap[i][j] = blockHeight;
        }
    }

    SoftHeight(HeightMap);
    //HardHeight(HeightMap);


    for(int i = 0 ; i < width ; i++) {
        for(int j = 0 ; j < height ;j ++) {
            float e = elavationMap[i][j];
            int blockHeight = HeightMap[i][j];
            int blockType = 0;
            if(e < 0.03f) {          // Water Level
                blockType = WATER;
            }else if(e < 0.04f) {    // Sand Level
                blockType = SAND;
            } else if(e < 0.4f) {   // Dirt Level

                blockType = DIRT;
            } else {                // Stone Level

                blockType = STONE;
            }

            for(int numTop = 0 ; numTop < blockHeight ; numTop++) {
                glm::vec3 position = glm::vec3(i * settings -> getBlockNDCSize().x - (width/2) * settings -> getBlockNDCSize().x, numTop * settings -> getBlockNDCSize().y , j * settings -> getBlockNDCSize().z - (height/2) * settings -> getBlockNDCSize().z) + origin;
                switch (blockType) {
                    case WATER :
                        blocks.push_back(std::make_unique<Water>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        //blocks.push_back(std::make_unique<Dirt>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        break;
                    case SAND :
                        blocks.push_back(std::make_unique<Sand>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        //blocks.push_back(std::make_unique<Dirt>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        break;
                    case DIRT :   
                        if(numTop == blockHeight - 1) {
                            blocks.push_back(std::make_unique<Grass>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                            //blocks.push_back(std::make_unique<Stone>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));

                        } else {
                            blocks.push_back(std::make_unique<Dirt>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                            
                        }
                         break;
                    case STONE :
                        blocks.push_back(std::make_unique<Stone>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        break;
                }
            }
        }
    }
    
}