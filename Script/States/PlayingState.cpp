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

    breakingBox = std::make_unique<AnimationBox>(4, "Assets/breaking.png", 16);
    ShaderManager::GetInstance() -> addShader("tool", "Shader/tool.vs", "Shader/tool.fs");
    handModel = nullptr;
}

PlayingState::~PlayingState() {
    delete m_instance;
}

void PlayingState::ProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection, const float &deltaTime) {
    MouseProcess(camera, chunkManager, view, projection);

    if(BlockChoose != -1) {
        timer.Update(deltaTime);
    }
        
    
    if(handModel) {
        handModel -> update(deltaTime);
        handModel -> render(view , projection);
    }

}

void PlayingState::MouseProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    {
        std::shared_ptr<Item> item = player -> getCurrentItem();
        if(item != nullptr) {

            if((handModel == nullptr) || (handModel && handModel -> getID() != item -> getID()) ) {
                
                int id = item -> getID();
                if(id < (int) BLOCKID::TOTAL ) {
                    handModel = std::make_unique<BlockModel>(glm::vec3(0.45f));
                    handModel -> addData(std::dynamic_pointer_cast<BlockItem>(item) -> getID());
                }else {
                    handModel = std::make_unique<ItemModel>(glm::vec3(1.f), "Assets/Items/items.png");
                    handModel -> addData(id);
                }
            }
        }else {
            if((handModel == nullptr) || (handModel && handModel -> getID() != (int) BLOCKID::Hand) ) {
                handModel = std::make_unique<BlockModel>(glm::vec3(0.35f));
                handModel -> addData( (int)BLOCKID::Hand);
            }
        }
    }
    if(player -> isOpeningInventory()) {
        double xpos,ypos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
        
        float x = xpos;
        float y = ypos;

        SPA::convertToNDC(x, y, Config::GetInstance() -> GetWidth(), Config::GetInstance() -> GetHeight());
        
        player -> InventoryUpdate(x , y, cursor -> GetInput());
        

        MouseHoldingItem = player -> getCurrentItem();
        return ;
    }
    
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

    if(input == Cursor::MOUSE_EVENT::LEFT_CLICK) {
        if(handModel != nullptr) {
            handModel -> BeingHit();
        }
    }

    if(exists == false) return ;

    if(input == Cursor::MOUSE_EVENT::LEFT_CLICK || input == Cursor::MOUSE_EVENT::LEFT_HOLD) {
        ChunkBlock block = chunkManager.getBlock(blockPosition.x, blockPosition.y, blockPosition.z);
        
        std::shared_ptr<Item> item = player -> getCurrentItem();

        
        
        int id = -1;
        if(item != nullptr) {
            id = item -> getID();
        }

        if(handModel != nullptr) {
            handModel -> BeingContinuosHit();
        }

        if( (int) block.getID() == BlockChoose && timer.isFinished() && id == timer.getInUse() && blockPosition == timer.getBlockPosition()) {
            
            chunkManager.removeBlock(blockPosition.x, blockPosition.y, blockPosition.z);
            SoundManager::GetInstance() -> PlaySound("Block");
            SoundManager::GetInstance() -> StopSound("Breaking");
            if(ItemConst::validTool( (int)block.getID(), id)) {
                int itemID = ItemConst::getItemDrop((int)block.getID());
                player -> addItem(itemID, 1);
                if(item != nullptr) {
                    player -> RemoveItem(item);
                }
            }
        }else if( (int) block.getID() != BlockChoose || id != timer.getInUse() || blockPosition != timer.getBlockPosition()) {
            BlockChoose = (int) block.getID();

            float efficiency = ItemConst::getItemEfficiency(id);

            if(!ItemConst::validEfficiency(id, (int)block.getID())) {
               efficiency = 0.f;
            }
            
            timer = Timer(Block::GetBlockHardness(BlockChoose), efficiency);
            if(item == nullptr) {
                timer.setInUse(-1);
            }else timer.setInUse((int)item->getID());

            SoundManager::GetInstance() -> PlaySoundEffect("Breaking");

            timer.setBlockPosition(blockPosition);
        }else {
            breakingBox -> Render(blockPosition, glm::vec3(1.f), timer.getCurrentTime(), timer.getMaxTime(), view, projection);
        }

        
        
    } else {
        BlockChoose = -1;
        timer.Reset();
        SoundManager::GetInstance() -> StopSound("Breaking");

        if(handModel != nullptr) {
            handModel -> StopContinuosHit();
        }
    }

    if(input == Cursor::MOUSE_EVENT::RIGHT_CLICK) {
        glm::vec3 position = blockPosition;

        ChunkBlock block = chunkManager.getBlock(position.x, position.y, position.z);
        if(handModel != nullptr) {
            handModel -> BeingHit();
        }
        if(block.getID() == BLOCKID::CraftingTable) { 
            player -> openInventory();
            if(player -> isOpeningInventory() == false) {
                throw std::runtime_error("Error");
            }

            Config * config = Config::GetInstance();
            config -> SetMouseActive(true);
            player -> UsingCraftingTable();

            return ;
        }
        
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
            BLOCKID id = (BLOCKID) std::dynamic_pointer_cast<BlockItem>(item) -> getID();
            if(id != BLOCKID::Air) {
                if(!player -> getColliding(box)) {
                    chunkManager.addBlock(position.x, position.y, position.z, ChunkBlock(id));
                    player -> RemoveItem(item);
                    SoundManager::GetInstance() -> PlaySound("Block");
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
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS && (player -> Flying() || player -> isUnderWater())) {
        force += camera.ProcessKeyboard(Camera_Movement::UP, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && (player -> Flying() || player -> isUnderWater())) {
        force += camera.ProcessKeyboard(Camera_Movement::DOWN, elapsedTime);
    }

    player -> addForce(force);
}


void PlayingState::FixedProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection)  {
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
        player -> CloseInventory();
    }


    glm::vec3 headPosition = player -> getPosition() - glm::vec3(0.f, 0.65f, 0.f);
    
    ChunkBlock block = chunkManager.getBlock(headPosition.x, headPosition.y, headPosition.z);
    if(block.getID() == BLOCKID::Water) {
        player -> isUnderWater(true);
    }else {
        player -> isUnderWater(false);
    }

    headPosition = player -> getHeadPosition();
    block = chunkManager.getBlock(headPosition.x, headPosition.y, headPosition.z);
    if(block.getID() == BLOCKID::Water) {
        player -> setHeadUnderWater(true);
    }else {
        player -> setHeadUnderWater(false);
    }
    

    
    Config * config = Config::GetInstance();
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        config -> SetMouseActive(true);
    }else if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE) {
        if(!player -> isOpeningInventory()) {

        
            config -> SetMouseActive(false);
        }
    }
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

void PlayingState::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    */
    //Config * config = Config::GetInstance();
    /*
    if(key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
        config -> SetMouseActive(true);
    }else if(key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) {
        config -> SetMouseActive(false);
    }
    */
}
