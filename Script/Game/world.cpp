#include "world.h"
// WorldRenderer Define

WorldRenderer *WorldRenderer :: instance = nullptr;

WorldRenderer :: WorldRenderer() {
    shaderManager = ShaderManager::getInstance();
    textureManager = TextureManager::getInstance();
    settings = Setting::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    player = Player::getInstance();
    CreateWorld();
}

WorldRenderer :: ~WorldRenderer() {
    delete instance;
}

void WorldRenderer :: Render(glm::mat4 view, glm::mat4 projection) {
    
    
    /*
    std::cout << "Frustum" << std::endl;
    std::cout << "Top Plane: " << frustum.topFace.normal.x << " " << frustum.topFace.normal.y << " " << frustum.topFace.normal.z << " " << frustum.topFace.distance << std::endl;
    std::cout << "Bottom Plane: " << frustum.bottomFace.normal.x << " " << frustum.bottomFace.normal.y << " " << frustum.bottomFace.normal.z << " " << frustum.bottomFace.distance << std::endl;
    std::cout << "Left Plane: " << frustum.leftFace.normal.x << " " << frustum.leftFace.normal.y << " " << frustum.leftFace.normal.z << " " << frustum.leftFace.distance << std::endl;
    std::cout << "Right Plane: " << frustum.rightFace.normal.x << " " << frustum.rightFace.normal.y << " " << frustum.rightFace.normal.z << " " << frustum.rightFace.distance << std::endl;
    std::cout << "Near Plane: " << frustum.nearFace.normal.x << " " << frustum.nearFace.normal.y << " " << frustum.nearFace.normal.z << " " << frustum.nearFace.distance << std::endl;
    std::cout << "Far Plane: " << frustum.farFace.normal.x << " " << frustum.farFace.normal.y << " " << frustum.farFace.normal.z << " " << frustum.farFace.distance << std::endl;
    */


    for (auto &block : blocks) {
        block -> Render(view, projection);
    }

}

void WorldRenderer :: Update(float deltaTime) {

    validBodies.clear();
    Frustum frustum = player -> extractFrustumPlanes();
    for (auto &block : blocks) {
        block -> PrepareRender(frustum);
        validBodies.push_back(block -> rigidbody);
        
    }
    for (auto &block : blocks) {
        block -> Update(deltaTime);
    }
}


void WorldRenderer::CreateWorld() {
    
    int width = 100;
    int height = 100;
    
         
    std::vector<std::vector<float>> elavationMap(width, std::vector<float>(height, 0));
    
    Frustum frustum = player -> extractFrustumPlanes();
    
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
                glm::vec3 position = glm::vec3(i * settings -> getBlockNDCSize().x - (width/2) * settings -> getBlockNDCSize().x, numTop * settings -> getBlockNDCSize().y , j * settings -> getBlockNDCSize().z);
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
