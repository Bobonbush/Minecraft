#include "PlayingState.h"

bool PlayingState::pressed[256];
PlayingState * PlayingState::m_instance = nullptr;

PlayingState::PlayingState() {
    for(int i = 0 ; i < 256 ; i++) {
        pressed[i] = false;
    }
    player = Player::GetInstance();
    cursor = Cursor::GetInstance();
    entities.push_back(player);
    glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
}

PlayingState::~PlayingState() {
    delete m_instance;
}

void PlayingState::ProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    MouseProcess(camera, chunkManager, view, projection);

    
    
}

void PlayingState::MouseProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    int input = cursor -> GetInput();



    std::vector<glm::vec3> normal = Block::normals;




    Ray ray = Ray(camera);

    bool exists = false;
    glm::vec3 blockPosition = glm::vec3(0.f);
    glm::vec3 nearestRay;
    
    for(int i = 0 ; i < 300 ; i++) {
        float step_size = 0.025;
        ray.step(step_size);
        glm::vec3 position = ray.getRayEnd();
        nearestRay = position;
        
            //std::cout << x <<  " " << y << " " << z << std::endl;
        if(chunkManager.existsBlock(position.x, position.y, position.z)) {
                //std::cout << x <<  " " << y << " " << z << std::endl;
            exists = true;
            blockPosition = chunkManager.getBlockPosition(position.x, position.y, position.z);

            hitBox.Draw(blockPosition, glm::vec3(1.f), view, projection);
            
            
            break;
        }
    }

    if(exists == false) return ;

    if(input == Cursor::MOUSE_EVENT::LEFT_CLICK) {
        ChunkBlock block = chunkManager.getBlock(blockPosition.x, blockPosition.y, blockPosition.z);
        chunkManager.removeBlock(blockPosition.x, blockPosition.y, blockPosition.z);
        player -> addBlockItem(block.getID(), 1);
    }

    if(input == Cursor::MOUSE_EVENT::RIGHT_CLICK) {
        glm::vec3 position = blockPosition;
        //glm::vec3 normalize = glm::vec3(0.f);
        float distance = 10000.f;
        for(int i = 0 ; i < 6 ; i++) {
            glm::vec3 surface = normal[i] + blockPosition;
            float dist = glm::distance(surface, nearestRay);
            if(dist < distance) {
                distance = dist;
                position = surface;
            }
        }

        std::shared_ptr<Item> item = player -> getCurrentItem();
        
        if(item != nullptr && item -> getType() == "Block") {
            AABB box(glm::vec3(1.f * Chunk::CHUNK_SCALE));
            box.update(position);
            BLOCKID id = std::dynamic_pointer_cast<BlockItem>(item) -> getID();
            if(id != BLOCKID::Air) {

            
                if(!player -> getColliding(box)) {
                    chunkManager.addBlock(position.x, position.y, position.z, ChunkBlock(id));
                    player -> RemoveItem(item);
                }
            }
        }
        
    }
    
}

void PlayingState::EntityProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    for(DYNAMIC_ENTITY * &entity : entities) {
        float distance = 2.f;
        std::vector<AABB> hitboxes;
        for(int x = -distance; x <= distance ; x++) {
            for(int y = -distance; y <= distance ; y++) {
                for(int z = -distance; z <= distance ; z++) {
                    glm::vec3 position = entity -> getPosition() + glm::vec3(x, y, z) * static_cast<float>(Chunk::CHUNK_SCALE);
                    
                    if(chunkManager.existsBlock(position.x, position.y, position.z)) {
                        
                        glm::vec3 blockPosition = chunkManager.getBlockPosition(position.x, position.y, position.z);
                        hitboxes.push_back(AABB(glm::vec3(Chunk::CHUNK_SCALE)));
                        hitboxes.back().update(blockPosition);
                    }
                }
            }
        }

        entity -> addCollisioner(hitboxes);
    }
}

void PlayingState::PlayerProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    glm::vec3 force = glm::vec3(0.f);
    float elapsedTime = 1.f;
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::FORWARD, elapsedTime);
    }
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::BACKWARD, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::LEFT, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::RIGHT, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS && player -> Flying()) {
        force += camera.ProcessKeyboard(Camera_Movement::UP, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && player -> Flying()) {
        force += camera.ProcessKeyboard(Camera_Movement::DOWN, elapsedTime);
    }

    player -> addForce(force);
}


void PlayingState::FixedProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection)  {

    for(int i = 0 ; i < 256 ; i++) {
        if( i == GLFW_KEY_C && pressed[i] == true && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) == GLFW_RELEASE) {
            player -> setFlying(!player -> Flying());
            pressed[i] = false;
        }

        if(pressed[i] == true && i == GLFW_KEY_E && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_RELEASE) {
            player -> openInventory();
            if(player -> isOpeningInventory()) {
                Config * config = Config::GetInstance();
                config -> SetMouseActive(true);
            }
            else {
                Config * config = Config::GetInstance();
                config -> SetMouseActive(false);
            }

            pressed[i] = false;
        }

        if(glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS) {
            pressed[i] = true;
        }

        
    }

    PlayerProcess(camera, chunkManager, view, projection);
    EntityProcess(camera, chunkManager, view, projection);
}
