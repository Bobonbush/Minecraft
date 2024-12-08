#ifndef INVENTORYBOX_H
#define INVENTORYBOX_H
#include "Texture.h"
#include "Item/Item.h"
#include "Texture&Shader/TextureManager.h"
#include "Renderer/SpriteRenderer.h"
#include "Config.h"
#include "Inventory.h"
#include "Algorithm.h"


class InventoryBox {
    private:
        bool m_chosen = false;
        unsigned int m_texture[2];  // on and off
        glm::vec2 m_position;
        glm::vec2 m_size;
        bool empty = true;

        std::shared_ptr<Item> item;

        int number = -1;

        SpriteRenderer* m_spriteRenderer;

        static std::unique_ptr<TextHandler> textLoader;
    public :
        InventoryBox(glm::vec2 position, glm::vec2 size, int number);
        ~InventoryBox();

        void update();
        void Render();

        void isChosen() {
            m_chosen = true;
        }

        void setItem(std::shared_ptr<Item> _item) {
            item = _item;
            empty = false;
        }

        void unsetItem() {
            item = nullptr;
            empty = true;
        }
};

#endif // INVENTORYBOX_H