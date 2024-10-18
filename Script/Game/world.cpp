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
            float nx = (float)i / width - 0.5f;
            float ny = (float)j / height - 0.5f;

            float frequency = 6.25f;
            elavationMap[i][j] = frequency * (db::perlin(2 * nx * frequency, 2 * ny * frequency) ) + frequency/2.f * (db::perlin(4 * nx * frequency, 4 * ny * frequency) ) + frequency/4.f * (db::perlin(8 * nx * frequency, 8 * ny * frequency) ) + frequency/8.f * (db::perlin(16 * nx * frequency, 16 * ny * frequency) );

            elavationMap[i][j] = elavationMap[i][j]/(frequency + frequency/2.f + frequency/4.f + frequency/8.f);
        }
    }

    for(int i = 0 ; i < width ; i++) {
        for(int j = 0 ; j < height ;j ++) {
            elavationMap[i][j] = (elavationMap[i][j] + 1.f) / 2.f ;
            std::cout << elavationMap[i][j] << " ";
        }
        std::cout << std::endl;
    }


    SoftNoise(elavationMap);

    for(int i = 0 ; i < width ; i++) {
        for(int j = 0 ; j < height ;j ++) {
            float e = elavationMap[i][j];
            int blockHeight = 0;
            int blockType = 0;
            if(e < 0.4f) {          // Water Level
                blockHeight = 1;
                blockType = WATER;
            }else if(e < 0.5f) {    // Sand Level
                blockHeight = SPA::RandomInt(1, 3);
                blockType = SAND;
            } else if(e < 0.7f) {   // Dirt Level
                blockHeight = SPA::RandomInt(5, 9);

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
