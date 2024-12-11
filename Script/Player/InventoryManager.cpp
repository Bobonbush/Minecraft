#include "InventoryManager.h"


InventoryManager::InventoryManager() {
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
    glm::vec2 position = glm::vec2(0.5f , 0.5f);

    offset = 0.005f;

    position.y = -1.f + size.y/2.f;
    position.x = 0.f - (size.x * Inventory::handCol/2) + offset * Inventory::handCol/2;

    sections.push_back(std::make_unique<InventorySection>(position, size, 1, Inventory::handCol, InventorySection::Type::Hand));



    position = glm::vec2(0.0f, 0.0f);
    position.y = -0.5f + size.y * Inventory::MAX_ROW/2.f - offset * Inventory::MAX_ROW/2;
    position.x = 0.f - (size.x * Inventory::MAX_COL/2) + offset * Inventory::MAX_COL/2;

    sections.push_back(std::make_unique<InventorySection>(position, size, Inventory::MAX_ROW-1, Inventory::MAX_COL, InventorySection::Type::Inventory));
    chosenKey[0] = true;
    sections[0] -> Activation();
    sections[1] -> Activation();

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
    sections.back() -> Activation();
    position = glm::vec2(0.0f, 0.0f);
    position.y = 0.5f + size.y * 3.f/2.f - offset * 3.f/2.f;
    position.x = 0.f - (size.x * 3.f/2) * 1.f/(aspect) * 1.5f + offset * 3.f/2 ;




    sections.push_back(std::make_unique<InventorySection>(position, size, 3, 3, InventorySection::Type::CraftingTable));
    //sections.back() -> Activation();

    addItem( (int)BLOCKID::Grass, 64);
    addItem((int)ItemID::Blue_Sword, 1);
    addItem((int)ItemID::Iron_Axe, 1);
    addItem((int)ItemID::Bow, 1);
    addItem((int)ItemID::Arrow, 64);
    addItem((int)ItemID::Iron_Pickage, 3);
    addItem((int)ItemID::Iron_Helmet, 1);
    addItem((int)ItemID::Copper_Chestplate, 1);
    addItem((int)ItemID::Laser_Leggings, 1);
    addItem((int)ItemID::Blue_Boots, 1);
    addItem((int) BLOCKID::Wood, 64);
    addItem((int)BLOCKID::TearWood, 64);

    addItem((int)BLOCKID::CraftingTable, 1);
    
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


std::pair<int ,int > InventoryManager::FindSlotForItem(int id) {
    
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


std::pair<int ,int> InventoryManager::FindItem(int id) {
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

    
        std::pair<int, int> pos = FindSlotForItem( (int) id);
        if(pos.first == -1) return ;   
        if(items[pos.first][pos.second] != nullptr) {
            number = items[pos.first][pos.second] -> addNumber(number);
            continue;
        } 
    
        items[pos.first][pos.second] = std::make_shared<BlockItem>(id, Block::blockMap[(int)id]); 
        if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
            sections[0] -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second);
        }else {
            sections[1] -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second  - Inventory::handCol);
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
        sections[0] -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col);
    }else {
        sections[1] -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col - Inventory::handCol);
    }
    number = items[row][col] -> addNumber(number);
    return number;

}

void InventoryManager::addSpriteItem(ItemID id , int number) {
    while(number > 0) {
        std::pair<int, int> pos = FindSlotForItem((int) id);
        if(pos.first == -1) return ;
        if(items[pos.first][pos.second] != nullptr) {
            number = items[pos.first][pos.second] -> addNumber(number);
            continue;
        }
        items[pos.first][pos.second] = std::make_shared<SpriteItem>(id, ItemDataBase::GetInstance() -> getItemName(id));    
        if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
            sections[0] -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second);
        }else {
            sections[1] -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second - Inventory::handCol);
        }
        number = items[pos.first][pos.second] -> addNumber(number);
    }

}

int InventoryManager::addSpriteItem(ItemID id ,int number ,int row ,int col) {
    if(items[row][col] != nullptr) {
        return items[row][col] -> getNumber();
    }
    items[row][col] = std::make_shared<SpriteItem>(id, ItemDataBase::GetInstance() -> getItemName(id));
    if(row * Inventory::MAX_COL + col < Inventory::handCol) {
        sections[0] -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col);
    }else {
        sections[1] -> setBoxItem(items[row][col], row * Inventory::MAX_COL + col - Inventory::handCol);
    }
    number = items[row][col] -> addNumber(number);
    return number;
}

void InventoryManager::addItem(int id ,int number) {
    if(id < (int) BLOCKID::TOTAL) {
        addBlockItem((BLOCKID) id, number);
    }else {
        addSpriteItem((ItemID) id, number);
    } 
}

void InventoryManager::addItem(int id , int number ,int row ,int col) {
    if(id < (int) BLOCKID::TOTAL) {
        addBlockItem((BLOCKID) id, number, row, col);
    }else {
        addSpriteItem((ItemID) id, number, row, col);
    }
}

void InventoryManager::RemoveItem(std::shared_ptr<Item> item)  {
    std::pair<int ,int> pos = FindItem(item -> getID());
    if(items[pos.first][pos.second] != nullptr) {
        items[pos.first][pos.second] -> use();
        if(items[pos.first][pos.second] -> getNumber() == 0) {
            items[pos.first][pos.second] = nullptr;
            if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
                sections[0] -> unsetBoxItem(pos.first * Inventory::MAX_COL + pos.second);
            }
        }
    }
}

void InventoryManager::RemoveItem(int row , int col) {
    if(items[row][col] != nullptr) {
        items[row][col] = nullptr;
        if(row * Inventory::MAX_COL + col < Inventory::handCol) {
            sections[0] -> unsetBoxItem(row * Inventory::MAX_COL + col);
        }

    }
}

void InventoryManager::update() {
    
    if(currentItemChoose != nullptr && currentItemChoose -> isPick == true) {
        currentItemChoose -> update();
    
    }
    for(std::unique_ptr<InventorySection> & section : sections) {
        if(!section -> isActive()) {
            continue;
        }
        section -> update();
    }

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
            sections[0] -> ChooseItem(i);
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
            if(!section -> isActive()) {
                continue;
            }
            section -> Render();
        }

        if(currentItemChoose != nullptr && currentItemChoose -> isPick == true) {
            currentItemChoose -> Render();
        }
        return ;
    }
    sections[0] -> Render();
    //handBox -> Render();
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

void InventoryManager::CloseInventory() {
    ShowInventory = false;
}


void InventoryManager::MouseUpdate(const float & xpos , const float & ypos) {
    if(!ShowInventory) {
        return ;
    }

    if(currentItemChoose != nullptr) {
        currentItemChoose -> setPosition(glm::vec3(xpos, ypos, 0.0f));
    }

    for(std::unique_ptr<InventorySection> & section : sections) {
        if(!section -> isActive()) {
            continue;
        }
        section -> MouseUpdate(xpos, ypos);
    }

    for(int i = 0; i < Inventory::handCol; i++) {
        items[0][i] = sections[0] -> getItem(0, i);
    }

    for(int i = 0; i < Inventory::MAX_ROW - 1; i++) {
        for(int j = 0; j < Inventory::MAX_COL; j++) {
            items[i+1][j] = sections[1] -> getItem(i, j);
        }
    }

}
void InventoryManager::PickItem() {

    if(currentItemChoose != nullptr) {
        currentItemChoose -> Drop();
        for(std::unique_ptr<InventorySection> & section : sections) {
            if(section -> isActive()) {

                if(section -> PlaceItem(currentItemChoose) || currentItemChoose == nullptr) {
                    return ;
                }
            }
        }

        if(currentItemChoose != nullptr) {
            currentItemChoose -> PickUp();
        }
        return ;
    }
    for(std::unique_ptr<InventorySection> & section : sections) {
        if(section -> isActive()) {
            section -> PickItem();
            currentItemChoose = section -> getCursorItem();
            if(currentItemChoose != nullptr) {
                currentItemChoose -> PickUp();
                break;
            }
        }
    }
}

void InventoryManager::PlaceOneItem() {
    if(currentItemChoose == nullptr) return ;
    for(std::unique_ptr<InventorySection> & section : sections) {
        if(section -> isActive()) {
            if(section -> PlaceItem(currentItemChoose, true)) {
                return ;
            }
        }
    }
}



void InventoryManager::UsingCraftingTable() {
    sections[2] -> Disactivation();
    sections[3] -> Disactivation();
    sections[4] -> Activation();
}

void InventoryManager::UsingNormalInventory() {
    sections[2] -> Activation();
    sections[3] -> Activation();
    sections[4] -> Disactivation();
}