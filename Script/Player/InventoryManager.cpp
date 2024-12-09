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
    
    float offset = 0.005f;
    glm::vec2 position = glm::vec2(0.0f , 0.0f);
    position.y = -0.5f + size.y * Inventory::MAX_ROW/2.f - offset * Inventory::MAX_ROW/2;
    position.x = 0.f - (size.x * Inventory::MAX_COL/2) + offset * Inventory::MAX_COL/2;

    sections.push_back(std::make_unique<InventorySection>(position, size, Inventory::MAX_ROW-1, Inventory::MAX_COL, InventorySection::Type::Inventory));
    chosenKey[0] = true;

    addBlockItem(BLOCKID::Grass, 64);
    
}

InventoryManager::~InventoryManager() {
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

void InventoryManager::RemoveItem(std::shared_ptr<Item> item)  {
    std::pair<int ,int> pos = FindItem(item -> getID());
    if(items[pos.first][pos.second] != nullptr) {
        items[pos.first][pos.second] -> use();
        if(items[pos.first][pos.second] -> getNumber() == 0) {
            items[pos.first][pos.second] = nullptr;
            if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
                handBox -> unsetBoxItem(pos.first * Inventory::MAX_COL + pos.second + 1);
            }
        }
    }
}

void InventoryManager::update() {

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

    for(int i = 0 ; i < Inventory::handCol ; i++) {
        if(chosenKey[i]) {
            handBox -> ChooseItem(i+1);
            currentItem = i;
        }
    }

}

void InventoryManager::Render() {
    if(ShowInventory) {
        for(std::unique_ptr<InventorySection> & section : sections) {
            section -> Render();
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
