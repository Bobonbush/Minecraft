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

    chosenKey[0] = true;

    addBlockItem(BLOCKID::Grass, 1);
    addBlockItem(BLOCKID::Dirt, 1);
    addBlockItem(BLOCKID::Stone, 1);
    addBlockItem(BLOCKID::Wood, 1);
    
}

InventoryManager::~InventoryManager() {
}


std::pair<int ,int > InventoryManager::FindItem(BLOCKID id) {
    
    std::pair<int ,int > nearest_Empty = std::make_pair(-1, -1);
    for(int i = 0; i < Inventory::MAX_ROW; i++) {
    for(int j = 0; j < Inventory::MAX_COL; j++) {
            if(items[i][j] == nullptr) {
                if(nearest_Empty.first == -1) {
                    nearest_Empty = std::make_pair(i, j);
                }
                continue;
            }

            if(id == items[i][j] -> getID()) {

                return std::make_pair(i, j);
            }
        }
    }
    return nearest_Empty;
}

void InventoryManager::addBlockItem(BLOCKID id, int number) {
    std::pair<int, int> pos = FindItem(id);
    if(pos.first == -1) return ;

    items[pos.first][pos.second] = std::make_shared<BlockItem>(id, number, Block::blockMap[(int)id]); 
    if(pos.first * Inventory::MAX_COL + pos.second < Inventory::handCol) {
        handBox -> setBoxItem(items[pos.first][pos.second], pos.first * Inventory::MAX_COL + pos.second + 1);
    }
    
}

void InventoryManager::update() {
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
    handBox -> Render();
}


