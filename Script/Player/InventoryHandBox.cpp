#include "InventoryHandBox.h"

InventoryHandBox::InventoryHandBox() {
    position = glm::vec2(0.5f, 0.5f); // Top Left
    color = glm::vec3(1.f);
    Config * config = Config::GetInstance();

    float aspect = 1.f/config -> GetAspectRatio();
    
    size = glm::vec2(Inventory::BoxSize.x * aspect, Inventory::BoxSize.y);
    float offset = 0.005f;
    position.y = -1.f + size.y/2.f;
    position.x = 0.f - (size.x * Inventory::handCol/2) + offset * Inventory::handCol/2;

    for(int i = 0; i < Inventory::handCol; i++) {
        box[i] = std::make_unique<InventoryBox>(glm::vec2(position.x + i * size.x - offset * i, position.y), size, i+1, "Assets/Inventory/off.png", InventoryBox::State::None);
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


}

std::shared_ptr<Item>InventoryHandBox::getItem(){
    return item;
}

void InventoryHandBox::ChooseItem(int number) {
    box[number -1] -> isChosen();
}

void InventoryHandBox::setBoxItem(std::shared_ptr<Item> _item, int number) {
    box[number - 1] -> setItem(_item);
}

void InventoryHandBox::unsetBoxItem(int number) {
    box[number - 1] -> unsetItem();
}


bool InventoryHandBox::FreeSlot() {
    for(int i = 0; i < Inventory::handCol; i++) {
        if(box[i] -> isEmpty()) {
            return true;
        }
    }
    return false;
}

void InventoryHandBox::MouseUpdate(const float &xpos, const float &ypos) {
    for(int i = 0; i < Inventory::handCol; i++) {
        if(box[i] -> isMouseOnBox(xpos, ypos)) {
            box[i] -> isChosen();
        }
    }
}
