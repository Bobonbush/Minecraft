#ifndef INVENTORYBOX_H
#define INVENTORYBOX_H
#include "Renderer/SpriteRenderer.h"
#include "Texture&Shader/TextureManager.h"



class InventoryBox {
    private:
        SpriteRenderer* spriteRenderer; 
        unsigned int texture[2];
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;

        int number = -1;       // -1 is empty
    public:
        InventoryBox();
        ~InventoryBox();

        void update();
        void RenderNumber();
        void Render();
        
};

#endif