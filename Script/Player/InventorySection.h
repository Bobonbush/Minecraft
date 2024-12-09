#ifndef INVENTORYSECTION_H
#define INVENTORYSECTION_H
#include "Inventory.h"
#include "InteractiveBox.h"
#include <vector>

class InventorySection {

    public :
        enum Type {
            Inventory,
            Crafting,
            Chest,
            Furnace,
            Weapon
        };

    private :
        std::vector<std::vector<std::shared_ptr<InventoryBox>>> Boxes;
        std::shared_ptr<Item> item;
        SpriteRenderer* spriteRenderer; // For behind renderer
        int numROW = Inventory::MAX_ROW;
        int numCOLLUM = Inventory::MAX_COL;
        glm::vec2 position;

        glm::vec2 size;

        Type type;

        
        

        
    public :

        
        

        InventorySection(const glm::vec2 & position, const  glm::vec2& size, int row, int col, const Type &type);
        ~InventorySection();

        void update();
        void Render();

        std::shared_ptr<Item> getItem();
        void ChooseItem(int number);
        void setBoxItem(std::shared_ptr<Item> _item, int number);
        void unsetBoxItem(int number);
        const Type getType() const;
        void setType(const Type & type);



};

#endif // INVENTORYSECTION_H