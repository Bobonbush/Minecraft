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

        int m_number = 0;
        unsigned int fakeTexture = -1;
        bool hasFake = false;
    public :
    
        enum class State : int {
                HEAD = 1,
                BODY = 2,
                LEG = 3,
                Boot = 4,
                None = 0 
        };
        InventoryBox(glm::vec2 position, glm::vec2 size, int number, const std::string& off, const State & state);
        ~InventoryBox();

        void update();
        void Render();

        void isChosen();

        void setItem(std::shared_ptr<Item> _item);
        void unsetItem();

        bool isEmpty();

        bool Choose();
};

#endif // INVENTORYBOX_H