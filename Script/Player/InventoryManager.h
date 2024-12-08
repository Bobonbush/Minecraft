#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H
#include "InventoryHandBox.h"
#include "InventoryBuilder.h"
#include "Block/Block.h"
class InventoryManager {
    private:
        std::unique_ptr<InventoryHandBox> handBox;
        std::vector<std::vector<std::shared_ptr<Item>>> items;   // Bot-Left pivot

        bool chosenKey[Inventory::handCol];

        int currentItem = 0;
    public :
        InventoryManager();
        ~InventoryManager();
        
        void update();
        void Render();

        std::shared_ptr<Item> getCurrentItem() {
            return items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL];
        }

        std::shared_ptr<Item> GetItem(int row, int col) {
            return items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL];
        }
        void addItem(std::shared_ptr<Item> item, int row, int col) {
            items[currentItem / Inventory::MAX_COL][currentItem % Inventory::MAX_COL] = item;
        }
        
        void RemoveItem( std::shared_ptr<Item> item);

        std::pair<int,int> FindItem(BLOCKID  id);
        void addBlockItem(BLOCKID id, int number);
};

#endif // INVENTORYMANAGER_H