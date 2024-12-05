#include "InventoryBox.h"

InventoryBox::InventoryBox() {
    // Empty
    TextureManager * textureManager = TextureManager::getInstance();
    
    texture[0] = textureManager -> getTexture("Assets/Inventory/box.png");
    texture[1] = textureManager -> getTexture("Assets/Inventory/on_box.png");
    
    spriteRenderer = SpriteRenderer::getInstance();
}


InventoryBox::~InventoryBox() {
    // Empty
}

void InventoryBox::update() {
    // Empty
}

void InventoryBox::RenderNumber() {
    if(number == -1) {
        return ;
    }
    TextureManager * textureManager = TextureManager::getInstance();
    unsigned int text = textureManager -> getTexture("Assets/Inventory/number.png");
    
}

void InventoryBox::Render() {
    spriteRenderer -> DrawSprite(texture[0], position, size, 0.0f, color, glm::mat4(1.0f), glm::mat4(1.0f));
}