#ifndef INVENTORYBOX_H
#define INVENTORYBOX_H
#include "Texture.h"
#include "Item.h"


class InventoryBox {
    private:
        bool m_chosen = false;
        unsigned int m_texture[2];  // on and off
        glm::vec2 m_position;
        glm::vec2 m_size;
        glm::vec3 m_color;
    public :
        InventoryBox();
        ~InventoryBox();

        void update();
        void Render();    
};

#endif // INVENTORYBOX_H