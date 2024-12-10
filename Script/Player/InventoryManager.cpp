#include "InventoryManager.h"


InventoryManager::InventoryManager() {
    handBox = std::make_unique<InventoryHandBox>();
    items.resize(Inventory::MAX_ROW);
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
        items[i].resize(Inventory::MAX_COL);
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            items[i][j] = nullptr;
        }
    }

    for(int i = 0; i < Inventory::handCol; i++) {
        chosenKey[i] = false;
    }

    for(int i = 0; i < Inventory::MAX_ROW; i++) {
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            items[i][j] = nullptr;
        }
    }

    for(int i = 0; i < Inventory::handCol; i++) {
        chosenKey[i] = false;
    }

    Config * config = Config::GetInstance();

    float aspect = 1.f/config -> GetAspectRatio();

    glm::vec2 size = glm::vec2(Inventory::BoxSize.x * aspect  , Inventory::BoxSize.y);
    size *= 1.f ;
    float offset = 0.005f;
    glm::vec2 position = glm::vec2(0.0f , 0.0f);
    position.y = -0.5f + size.y * Inventory::MAX_ROW/2.f - offset * Inventory::MAX_ROW/2;
    position.x = 0.f - (size.x * Inventory::MAX_COL/2) + offset * Inventory::MAX_COL/2;

    sections.push_back(std::make_unique<InventorySection>(position, size, Inventory::MAX_ROW-1, Inventory::MAX_COL, InventorySection::Type::Inventory));
    chosenKey[0] = true;
    sections[0] -> Activation();

    position = glm::vec2(position.x , 0.0f);

    //size *= 1.2f;
    offset = 0.075f;
    //position.x -= size.x/2.f;
    position.y = 0.5f + size.y * 4/2.f - offset * 4/2;

    sections.push_back(std::make_unique<InventorySection>(position, size, 4, 1, InventorySection::Type::Weapon));
    sections.back() -> Activation();
    position.x += size.x * 1.75 + offset * 2;
    position.y = 0.5f +  size.y * 4/2.f - offset * 4 /2.f;

    position.y -= size.y  + offset ;
    sections.push_back(std::make_unique<InventorySection>(position, size, 2, 2, InventorySection::Type::Crafting));
    addBlockItem(BLOCKID::Grass, 64);

    sections.back() -> Activation();
    
}

InventoryManager::~InventoryManager() {
}


std::pair<int ,int > InventoryManager::FindPickedUpItem() {
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            if(items[i][j] != nullptr && items[i][j] -> isPick) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

void InventoryManager::addItem(std::shared_ptr<Item> item, int row, int col) {
    if(items[row][col] != nullptr) {
        //items[row][col] -> addNumber(item -> getNumber());
        throw std::runtime_error("Cannot add more item");
        return ;
    }
    items[row][col] = item;
    if(row * Inventory::MAX_COL + col < Inventory::handCol) {
        handBox -> setBoxItem(item, row * Inventory::MAX_COL + col + 1);
    }else {
        sections[0] -> setBoxItem(item, row * Inventory::MAX_COL + col - Inventory::handCol);
    }
}

std::pair<int ,int> InventoryManager::FindPickedUpItem(std::shared_ptr<Item> item) {
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            if(items[i][j] == nullptr) continue;
            if(items[i][j] == item && items[i][j] -> isPick) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}


std::pair<int ,int > InventoryManager::FindSlotForItem(BLOCKID id) {
    
    std::pair<int ,int > nearest_Empty = std::make_pair(-1, -1);
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
    for(int j = 0; j < Inventory::MAX_COL; j++) {
            if(items[i][j] == nullptr ) {
                if(nearest_Empty.first == -1) {
                    nearest_Empty = std::make_pair(i, j);
                }
                continue;
            }

            if(id == items[i][j] -> getID() && items[i][j] -> isFull() == false) {
                return std::make_pair(i, j);
            }
        }
    }
    return nearest_Empty;
}


const std::shared_ptr<Item> InventoryManager::getCursorItem() const {
    return currentItemChoose;
}


std::pair<int ,int> InventoryManager::FindItem(BLOCKID id) {
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            if(items[i][j] != nullptr && items[i][j] -> getID() == id) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

void InventoryManager::addBlockItem(BLOCKID id, int number) {

    while(number > 0) {

    
        std::pair<int, int> pos = FindSlotForItem(id);
        if(pos.first == -1) return ;   
        if(items[pos.first][pos.second] != nullptr) {
            number = items[pos.first][pos.second] -> addNumber(number);
            continue;
        } 
    
        items[pos.first][pos.second] = std::make_shared<BlockItem>(id, Block::blockMap[(int)id]); 
        if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
            handBox -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second + 1);
        }else {
            sections[0] -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second  - Inventory::handCol);
        }
        number = items[pos.first][pos.second] -> addNumber(number);
    }
}

int InventoryManager::addBlockItem(BLOCKID id, int number, int row, int col) {
    if(items[row][col] != nullptr) {
        return items[row][col] -> getNumber(); // cannot add more
    }
    items[row][col] = std::make_shared<BlockItem>(id, Block::blockMap[(int)id]);
    if(row * Inventory::MAX_COL + col < Inventory::handCol) {
        handBox -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col + 1);
    }else {
        sections[0] -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col - Inventory::handCol);
    }
    number = items[row][col] -> addNumber(number);
    return number;

}

void InventoryManager::RemoveItem(std::shared_ptr<Item> item)  {
    std::pair<int ,int> pos = FindItem(item -> getID());
    if(items[pos.first][pos.second] != nullptr) {
        items[pos.first][pos.second] -> use();
        if(items[pos.first][pos.second] -> getNumber() == 0) {
            items[pos.first][pos.second] = nullptr;
            if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
                handBox -> unsetBoxItem(pos.first * Inventory::MAX_COL + pos.second + 1);
            }else {
                sections[0] -> unsetBoxItem(pos.first * Inventory::MAX_COL + pos.second - Inventory::handCol);
            }
        }
    }
}

void InventoryManager::RemoveItem(int row , int col) {
    if(items[row][col] != nullptr) {
        items[row][col] = nullptr;
        if(row * Inventory::MAX_COL + col < Inventory::handCol) {
            handBox -> unsetBoxItem(row * Inventory::MAX_COL + col + 1);
        }else if(row < Inventory::MAX_ROW && col < Inventory::MAX_COL){
            sections[0] -> unsetBoxItem(row * Inventory::MAX_COL + col - Inventory::handCol);
        }

    }
}

void InventoryManager::update() {
    
    if(currentItemChoose != nullptr && currentItemChoose -> isPick == true) {
        currentItemChoose -> update();
    }
    for(std::unique_ptr<InventorySection> & section : sections) {
        section -> update();
    }

    handBox -> update();
    for(int i = 0; i < Inventory::handCol; i++) {
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1 + i) == GLFW_PRESS) {
            for(int j = 0; j < Inventory::handCol; j++) {
                chosenKey[j] = false;
            }
            chosenKey[i] = true;
            break;
        }
    }

    for(int i = 0 ; i < Inventory::handCol && !ShowInventory ; i++) {
        if(chosenKey[i]) {
            handBox -> ChooseItem(i+1);
            currentItem = i;
        }
    }

}

void InventoryManager::Render() {
    if(ShowInventory) {

        
        SpriteRenderer * spriteRenderer = SpriteRenderer::getInstance();
        
        glm::vec2 position = glm::vec2(0.0f, 0.0f);
        glm::vec2 size = glm::vec2(2.0f, 2.0f);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("clear"));
        spriteRenderer -> DrawSprite(TextureManager::getInstance() -> getTexture("Assets/Inventory/clear.png"), position, size, 0.f, glm::vec3(1.f), glm::mat4(1.0f), glm::mat4(1.0f), 0.8f);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        
        for(std::unique_ptr<InventorySection> & section : sections) {
            section -> Render();
        }

        if(currentItemChoose != nullptr && currentItemChoose -> isPick == true) {
            currentItemChoose -> Render();
        }
    }
    handBox -> Render();
}

std::shared_ptr<Item> InventoryManager::getCurrentItem() {
    return items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL];
}

std::shared_ptr<Item> InventoryManager::GetItem(int row, int col) {
    return items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL];
}

void InventoryManager::setItem(std::shared_ptr<Item> item) {
    items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL] = item;
}

void InventoryManager::ShowInventoryBox() {
    ShowInventory ^= 1;
}


void InventoryManager::MouseUpdate(const float & xpos , const float & ypos) {

    if(currentItemChoose != nullptr && currentItemChoose -> isPick == true) {
        currentItemChoose -> setPosition(glm::vec3(xpos, ypos, 0.f));
    }else {
        currentItemChoose = nullptr;
    }
    handBox -> MouseUpdate(xpos, ypos);
    if(handBox -> getCursorItem() != nullptr) {
        if(currentItemChoose == nullptr || currentItemChoose -> isPick == false) {
            currentItemChoose = handBox -> getCursorItem();
        }
    }else {

    
        for(std::unique_ptr<InventorySection> & section : sections) {
            if(!section -> isActive()) {
                continue;
            }
            section -> MouseUpdate(xpos, ypos);
            if(section -> getCursorItem() != nullptr) {
    
                if(currentItemChoose == nullptr || currentItemChoose -> isPick == false) {
                    currentItemChoose = section -> getCursorItem();
                }
                break;
            }
        }
    }
}

void InventoryManager::PickItem() {
    if(currentItemChoose == nullptr) {
        return ;
    }

    if(currentItemChoose -> isPick == true) {
        currentItemChoose -> Drop();
        addItem(currentItemChoose, currentItemPosition.first, currentItemPosition.second);
        
        return ;
    }

    currentItemChoose -> PickUp();
    currentItemPosition = FindPickedUpItem();
    RemoveItem(currentItemPosition.first, currentItemPosition.second);
    
}