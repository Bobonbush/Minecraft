#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H
#include "Block/Block.h"
#include "InventorySection.h"
class InventoryManager {
    private:
        std::vector<std::vector<std::shared_ptr<Item>>> items; // All items inside Player's Inventory   // Bot-Left pivot

        bool chosenKey[Inventory::handCol];
        std::vector<std::unique_ptr<InventorySection>> sections;
        int currentItem = 0;

        bool ShowInventory = false;

        std::shared_ptr<Item> currentItemChoose;
        std::pair<int ,int> currentItemPosition = std::make_pair(-1 ,-1);

        std::pair<int ,int > FindPickedUpItem();
        std::pair<int ,int> FindPickedUpItem(std::shared_ptr<Item> item);

        void addBlockItem(BLOCKID id, int number);
        int addBlockItem(BLOCKID id, int number, int row, int col);
        void addSpriteItem(ItemID id ,int number);
        int addSpriteItem(ItemID id , int number, int row , int col);
    public :
        InventoryManager();
        ~InventoryManager();
        
        void update();
        void Render();

        const std::shared_ptr<Item> getCursorItem() const;
        

        std::shared_ptr<Item> getCurrentItem();  // Get the current item in hand

        std::shared_ptr<Item> GetItem(int row, int col);
        void RemoveItem( std::shared_ptr<Item> item);
        void RemoveItem(int row, int col);

        std::pair<int,int> FindSlotForItem(int id);
        std::pair<int,int> FindItem(int id);
        

        void addItem(int id ,int number);
        void addItem(int id , int number ,int row ,int col);

        void setItem(std::shared_ptr<Item> item);
        void ShowInventoryBox();

        void MouseUpdate(const float & xpos, const float & ypos);
        void PickItem();
        void PlaceOneItem();
};

#endif // INVENTORYMANAGER_H