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
    UnloadChunks();
    LoadChunks();

    for(auto & chunk : chunks) {
        std::vector<std::shared_ptr<Rigidbody>> subvalidBodies = chunk -> Update(deltaTime);
        for(auto & body : subvalidBodies) {
            validBodies.push_back(body);
        }
    }
}

void WorldRenderer:: LoadChunks() {
    glm::vec3 position = player -> GetPosition();
    bool Find = false;
    std::cout << "Player Position : " << position.x << " " << position.y << " " << position.z << '\n';
    glm::vec3 origin = player -> GetPosition();
    position.y = 0.f;
    for(auto &chunk : chunks) {
        glm::vec3 chunkPosition = chunk -> GetOrigin();

        glm::vec3 min = chunkPosition - glm::vec3(settings -> getChunkSize().x * settings -> getBlockNDCSize().x, 0.f, settings -> getChunkSize().y * settings -> getBlockNDCSize().z) /2.f;
        glm::vec3 max = chunkPosition + glm::vec3(settings -> getChunkSize().x * settings -> getBlockNDCSize().x, 0.f, settings -> getChunkSize().y * settings -> getBlockNDCSize().z) /2.f;
        
        if(position.x >= min.x && position.x <= max.x && position.z >= min.z && position.z <= max.z) {
            Find = true;
            origin = chunkPosition;
            break;
        }
    }

    std::cout << "Origin : " << origin.x << " " << origin.y << " " << origin.z << '\n';

    if(!Find) {
        glm::vec3 playerPosition = player -> GetPosition();
        origin = position;
        origin.y = 0.f;
        chunks.push_back(std::make_unique<Chunk>(origin));
        chunks.back() -> LoadChunk();
        //chunks.push_back(std::make_unique<Chunk>(origin + glm::vec3(settings -> getChunkSize().x * settings -> getBlockNDCSize().x, 0.f, 0.f)));
        
        
        //chunks.back() -> LoadChunk();
    }

    //return ;

    
    
    for(int x = -ChunkDiameter; x <= ChunkDiameter; x++) {
        for(int z = -ChunkDiameter; z <= ChunkDiameter; z++) {
            glm::vec3 new_origin = origin;
            new_origin.x += x * settings -> getChunkSize().x * settings -> getBlockNDCSize().x;
            new_origin.z += z * settings -> getChunkSize().y * settings -> getBlockNDCSize().z;
            bool Find = false;
            for(auto &chunk : chunks) {
                glm::vec3 chunkPosition = chunk -> GetOrigin();
                if(glm::distance(new_origin, chunkPosition) == 0) {
                    Find = true;
                    break;
                }
            }

            for(auto &chunk : WaitingChunks) {
                glm::vec3 chunkPosition = chunk -> GetOrigin();
                if(glm::distance(new_origin, chunkPosition) == 0) {
                    Find = true;
                    break;
                }
            }

            if(!Find) {
                //std::cout << new_origin.x << " " << new_origin.y << " " << new_origin.z << '\n';
                WaitingChunks.push_back(std::make_unique<Chunk>(new_origin));
                //chunks.push_back(std::make_unique<Chunk>(new_origin));
                //chunks.back() -> LoadChunk();
                ChunkLoadQueue.push(std::make_unique<Chunk>(new_origin));
            }
        }
    }

    if(!ChunkLoadQueue.empty()) {
        chunks.push_back(std::move(ChunkLoadQueue.front()));
        chunks.back() -> LoadChunk();
        ChunkLoadQueue.pop();
        for(int i = 0 ; i < (int)WaitingChunks.size()-1 ; i++) {
            if(WaitingChunks[i] -> GetOrigin() == chunks.back() -> GetOrigin()) {
                swap(WaitingChunks[i], WaitingChunks.back());
                WaitingChunks.pop_back();
                i--;
            }
        }
    }

}

void WorldRenderer::UnloadChunks() {

    glm::vec3 position = player -> GetPosition();
    position.y = 0.f;
    glm::vec3 origin = player -> GetPosition();

    
    for(auto &chunk : chunks) {
        glm::vec3 chunkPosition = chunk -> GetOrigin();
        glm::vec3 min = chunkPosition - glm::vec3(settings -> getChunkSize().x * settings -> getBlockNDCSize().x, 0.f, settings -> getChunkSize().y * settings -> getBlockNDCSize().z) /2.f;
        glm::vec3 max = chunkPosition + glm::vec3(settings -> getChunkSize().x * settings -> getBlockNDCSize().x, 0.f, settings -> getChunkSize().y * settings -> getBlockNDCSize().z) /2.f;
        
        if(position.x >= min.x && position.x <= max.x && position.z >= min.z && position.z <= max.z) {
            origin = chunkPosition;
            break;
        }
    }
    position = origin;
    for(int i = 0 ; i < (int)chunks.size()-1 ; i++) {
        glm::vec3 chunkPosition = chunks[i] -> GetOrigin();
        if(glm::distance(position, chunkPosition) > (ChunkDiameter ) * settings -> getChunkSize().x) {
            swap(chunks[i], chunks.back());
            chunks.pop_back();
            i--;
            std::cout << "Chunk Unloaded\n";
        }
    }
    
}