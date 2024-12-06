#ifndef INVENTORYHANDBOX_H
#define INVENTORYHANDBOX_H
#include "Renderer/SpriteRenderer.h"
#include "Texture&Shader/TextureManager.h"
#include "InteractiveBox.h"
#include "Inventory.h"


class InventoryHandBox {
    private:
        SpriteRenderer* spriteRenderer; 
        std::unique_ptr<InventoryBox> box[Inventory::handCol];
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        
        int number = -1;       // -1 is empty
    public:
        InventoryHandBox();
        ~InventoryHandBox();

        void update();
        void Render();
        
};

#endif