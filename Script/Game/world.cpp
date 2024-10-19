#include "world.h"
// WorldRenderer Define

WorldRenderer *WorldRenderer :: instance = nullptr;

WorldRenderer :: WorldRenderer() {
    shaderManager = ShaderManager::getInstance();
    textureManager = TextureManager::getInstance();
    settings = Setting::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    CreateWorld();
}

WorldRenderer :: ~WorldRenderer() {
    delete instance;
}

void WorldRenderer :: Render(glm::mat4 view, glm::mat4 projection) {
    for (auto &block : blocks) {
        block -> Render(view, projection);
    }
}

void WorldRenderer :: Update(float deltaTime) {
    for (auto &block : blocks) {
        block -> Update(deltaTime);
    }
}


void WorldRenderer::CreateWorld() {
            
    int width = 100;
    int height = 100;

    std::vector<std::vector<float>> elavationMap(width, std::vector<float>(height, 0));

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
            elavationMap[i][j] = pow(elavationMap[i][j], 3.f);
            //SPA::clamp(elavationMap[i][j], 0.f, 1.f);
            //std::cout << elavationMap[i][j] << " ";
        }
        //std::cout << std::endl;
    }


    SoftNoise(elavationMap);

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
                blockHeight = SPA::RandomInt(10, 15); 

                blockType = STONE;
            }

            for(int numTop = 0 ; numTop < blockHeight ; numTop++) {
                glm::vec3 position = glm::vec3(i * settings -> getBlockNDCSize().x - (width/2) * settings -> getBlockNDCSize().x, numTop * settings -> getBlockNDCSize().y , j * settings -> getBlockNDCSize().z);
                switch (blockType) {
                    case WATER :
                        blocks.push_back(std::make_unique<Water>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        break;
                    case SAND :
                        blocks.push_back(std::make_unique<Sand>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
                        break;
                    case DIRT :   
                        if(numTop == blockHeight - 1) {
                            blocks.push_back(std::make_unique<Grass>(position, settings -> getBlockNDCSize(), glm::vec3(0.0f, 0.0f, 0.0f), shaderManager -> GetShader("block")));
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
