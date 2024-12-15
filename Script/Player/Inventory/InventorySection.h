#ifndef INVENTORYSECTION_H
#define INVENTORYSECTION_H
#include "Inventory.h"
#include "InteractiveBox.h"
#include <vector>
#include "Player/Crafting/Recipe.h"

class InventorySection {

    public :
        enum Type {
            Hand,
            Inventory,
            Crafting,
            Chest,
            Furnace,
            Weapon,
            CraftingTable
        };

        static CraftingRecipeDataBase * recipe;

    private :
        std::vector<std::vector<std::shared_ptr<InventoryBox>>> Boxes;

        std::shared_ptr<InventoryBox> ResultBox;
        std::shared_ptr<InventoryBox> itemChoose;
        std::shared_ptr<Item> cursorItem;
        SpriteRenderer* spriteRenderer; // For behind renderer
        int numROW = Inventory::MAX_ROW;
        int numCOLLUM = Inventory::MAX_COL;
        glm::vec2 position;

        glm::vec2 size;

        bool Active = false;

        Type type;

        unsigned int rightArrow;

        glm::vec2 rightArrowPosition;
        glm::vec2 rightArrowSize;

        bool isResultBox = false;

        
        

        
    public :

        
        

        InventorySection(const glm::vec2 & position, const  glm::vec2& size, int row, int col, const Type &type);
        ~InventorySection();

        void update();
        void Render();

        std::shared_ptr<Item> getCursorItem();
        void ChooseItem(int number);
        void setBoxItem(std::shared_ptr<Item> _item, int number);
        void unsetBoxItem(int number);
        const Type getType() const;
        void setType(const Type & type);
        void MouseUpdate(const float & xpos, const float & ypos);
        
        bool isActive();
        bool Activation();
        bool Disactivation();

        bool PlaceItem(std::shared_ptr<Item> & item); // True if the item is placed or false if the item is not placed
        bool PlaceItem(std::shared_ptr<Item> & item, bool one);  // one is flag for right click 
        void PickItem();

        void CreateRecipe();

        std::shared_ptr<Item> getItem(int row, int col) {
            return Boxes[row][col] -> getItem();
        }
    



};

#endif // INVENTORYSECTION_H