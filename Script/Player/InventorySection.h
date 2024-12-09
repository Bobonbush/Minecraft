#ifndef INVENTORYSECTION_H
#define INVENTORYSECTION_H
#include "Inventory.h"
#include "InteractiveBox.h"
#include <vector>

class InventorySection {
    private :
        std::vector<std::vector<std::shared_ptr<InventoryBox>>> Boxes;
        std::shared_ptr<Item> item;
        SpriteRenderer* spriteRenderer; // For behind renderer
        int numCOLLUM = Inventory::MAX_COL;
        int numROW = Inventory::MAX_ROW;
        enum class state : int {
            HEAD = 1,
            BODY = 2,
            LEG = 3,
            Boot = 4,
            None = 0 
        };

        
    public :

        InventorySection(int state = 0);
        ~InventorySection();

        void update();
        void Render();

        std::shared_ptr<Item> getItem() {
            return item;
        }

        void ChooseItem(int number) {
            Boxes[number / numCOLLUM][number % numCOLLUM] -> isChosen();
        }

        void setBoxItem(std::shared_ptr<Item> _item, int number) {
            Boxes[number / numCOLLUM][number % numCOLLUM] -> setItem(_item);
        }

        void unsetBoxItem(int number) {
            Boxes[number / numCOLLUM][number % numCOLLUM] -> unsetItem();
        }



};

#endif // INVENTORYSECTION_H