#include "world.h"
// WorldRenderer Define

WorldRenderer *WorldRenderer :: instance = nullptr;

WorldRenderer :: WorldRenderer() {
    shaderManager = ShaderManager::getInstance();
    textureManager = TextureManager::getInstance();
    settings = Setting::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    player = Player::getInstance();
}

WorldRenderer :: ~WorldRenderer() {
    delete instance;
}

void WorldRenderer :: Render(glm::mat4 view, glm::mat4 projection) {
    for(auto & chunk : chunks) {
        chunk -> Render(view, projection);
    }
}

void WorldRenderer :: Update(float deltaTime) {
    
    validBodies.clear();
    Frustum frustum = player -> extractFrustumPlanes();
    LoadChunks();
    for(auto & chunk : chunks) {
        std::vector<std::shared_ptr<Rigidbody>> subvalidBodies = chunk -> Update(deltaTime);
        for(auto & body : subvalidBodies) {
            validBodies.push_back(body);
        }
    }
}

void WorldRenderer:: LoadChunks() {
    
}