#include "InventorySection.h"

InventorySection::InventorySection(const glm::vec2 & position, const  glm::vec2& size, int row, int col, const Type &type ) : position(position), size(size), numROW(row), numCOLLUM(col), type(type) {
    Boxes.resize(numROW);

    if(type == Type::Weapon) {
        InventoryBox::State states[4] = {InventoryBox::State::HEAD, InventoryBox::State::BODY, InventoryBox::State::LEG, InventoryBox::State::Boot};
        if(col != 4 || row != 1) {
            throw std::runtime_error("Weapon Inventory must have 4 columns and 1 row");
        }

        Boxes.resize(numROW);
        for(int i = 0; i < numROW; i++) {
            Boxes[i].resize(numCOLLUM);
            Boxes[i][0] = std::make_shared<InventoryBox>(glm::vec2(position.x, position.y - i * size.y), size, i + 1, "Assets/Inventory/off.png", states[i]);
        }
    }

    if(type == Type::Inventory) {

        float aspect = 1.f/Config::GetInstance() -> GetAspectRatio();
        for(int i = 0; i < numROW; i++) {

            const float offset = 0.005f;
            Boxes[i].resize(numCOLLUM);
            for(int j = 0; j < numCOLLUM; j++) {
                Boxes[i][j] = std::make_shared<InventoryBox>(glm::vec2(position.x + j * size.x - offset * j, position.y - i * size.y + offset / aspect * i), size, i * numCOLLUM + j + 1, "Assets/Inventory/off.png", InventoryBox::State::None);
            }
        }
    }

}

InventorySection::~InventorySection() {
}

void InventorySection::update() {
    for(int i = 0; i < numROW; i++) {
        for(int j = 0; j < numCOLLUM; j++) {
            Boxes[i][j] -> update();
        }
    }
}

void InventorySection::Render() {
    for(int i = 0; i < numROW; i++) {
        for(int j = 0; j < numCOLLUM; j++) {
            Boxes[i][j] -> Render();
        }
    }
}

std::shared_ptr<Item> InventorySection::getItem() {
    return item;
}

void InventorySection::ChooseItem(int number) {
    Boxes[number / numCOLLUM][number % numCOLLUM] -> isChosen();
}


void InventorySection::setBoxItem(std::shared_ptr<Item> _item, int number) {
    Boxes[number / numCOLLUM][number % numCOLLUM] -> setItem(_item);
}


void InventorySection::unsetBoxItem(int number) {
    Boxes[number / numCOLLUM][number % numCOLLUM] -> unsetItem();
}

const InventorySection::Type InventorySection::getType() const {
    return type;
}

void InventorySection::setType(const Type & type) {
    this -> type = type;
}


