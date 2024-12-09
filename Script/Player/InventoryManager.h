#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H
#include "InventoryHandBox.h"
#include "Block/Block.h"
#include "InventorySection.h"
class InventoryManager {
    private:
        std::unique_ptr<InventoryHandBox> handBox;
        std::vector<std::vector<std::shared_ptr<Item>>> items;   // Bot-Left pivot

        bool chosenKey[Inventory::handCol];
        std::vector<std::unique_ptr<InventorySection>> sections;
        int currentItem = 0;

        bool ShowInventory = false;
    public :
        InventoryManager();
        ~InventoryManager();
        
        void update();
        void Render();

        std::shared_ptr<Item> getCurrentItem();

        std::shared_ptr<Item> GetItem(int row, int col);
        void RemoveItem( std::shared_ptr<Item> item);

        std::pair<int,int> FindSlotForItem(BLOCKID  id);
        std::pair<int,int> FindItem(BLOCKID id);
        void addBlockItem(BLOCKID id, int number);

        void setItem(std::shared_ptr<Item> item);
        
        void SwapItem(int row ,int col ,int sectionNumber);
        void SwapItem(int row, int col, int row2 , int col2,  int sectionNumber1, int sectionNumber2);
        void SwapItem(int row, int col, int handCol, bool hand);
        void ShowInventoryBox();
};

#endif // INVENTORYMANAGER_H