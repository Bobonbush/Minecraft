#include "InventoryHandBox.h"

InventoryHandBox::InventoryHandBox() {
    position = glm::vec2(0.5f, 0.5f); // Top Left
    color = glm::vec3(1.f);
    Config * config = Config::GetInstance();

    float aspect = 1.f/config -> GetAspectRatio();

    size = glm::vec2(0.18f * aspect, 0.18f);
    float offset = 0.005f;
    position.y = -1.f + size.y/2.f;
    position.x = 0.f - (size.x * Inventory::handCol/2) + offset * Inventory::handCol/2;

    for(int i = 0; i < Inventory::handCol; i++) {
        box[i] = std::make_unique<InventoryBox>(glm::vec2(position.x + i * size.x - offset * i, position.y), size, i+1);
    }

    spriteRenderer = SpriteRenderer::getInstance();
}


InventoryHandBox::~InventoryHandBox() {
}

void InventoryHandBox::update() {
    for(int i = 0 ; i < Inventory::handCol; i++) {
        box[i] -> update();
    }
}

void InventoryHandBox::Render() {
    for(int i = 0; i < Inventory::handCol; i++) {
        box[i] -> Render();
    }

    Config * config = Config::GetInstance();

    float readlSizeX = size.x / config -> GetWidth() * 16; // 16 x 16 pic
    float readlSizeY = size.y / config -> GetHeight() * 16;

    

}