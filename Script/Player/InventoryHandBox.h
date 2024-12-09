#ifndef INVENTORYHANDBOX_H
#define INVENTORYHANDBOX_H
#include "Renderer/SpriteRenderer.h"

#include "InteractiveBox.h"
#include "Inventory.h"
#include "Config.h"


class InventoryHandBox {
    private:
        SpriteRenderer* spriteRenderer; 
        std::unique_ptr<InventoryBox> box[Inventory::handCol];
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;

        std::shared_ptr<InventoryBox> handBox;

        std::shared_ptr<Item> item;          // Item in hand

        int number = -1;
    public:
        InventoryHandBox();
        ~InventoryHandBox();

        void update();
        void Render();

        std::shared_ptr<Item> getItem();

        void ChooseItem(int number);


        void setBoxItem(std::shared_ptr<Item> _item, int number);

        void unsetBoxItem(int number);

        bool FreeSlot();
};

#endif