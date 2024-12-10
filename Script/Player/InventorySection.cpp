#include "InventorySection.h"

InventorySection::InventorySection(const glm::vec2 & position, const  glm::vec2& size, int row, int col, const Type &type ) : position(position), size(size), numROW(row), numCOLLUM(col), type(type) {
    Boxes.resize(numROW);

    ResultBox = nullptr;

    spriteRenderer = SpriteRenderer::getInstance();
    

    if(type == Type::Weapon) {
        InventoryBox::State states[4] = {InventoryBox::State::HEAD, InventoryBox::State::BODY, InventoryBox::State::LEG, InventoryBox::State::Boot};
        if(col != 1 || row != 4) {
            throw std::runtime_error("Weapon Inventory must have 4 columns and 1 row");
        }

        const float offset = 0.075f;
        for(int i = 0; i < numROW; i++) {
            Boxes[i].resize(numCOLLUM);
            Boxes[i][0] = std::make_shared<InventoryBox>(glm::vec2(position.x, position.y - i * size.y - offset * i), size, i + 1, "Assets/Inventory/off.png", states[i]);
        }
    }else if(type == Type::Inventory) {

        float aspect = 1.f/Config::GetInstance() -> GetAspectRatio();
        for(int i = 0; i < numROW; i++) {

            const float offset = 0.005f;
            Boxes[i].resize(numCOLLUM);
            for(int j = 0; j < numCOLLUM; j++) {
                Boxes[i][j] = std::make_shared<InventoryBox>(glm::vec2(position.x + j * size.x - offset * j, position.y - i * size.y + offset / aspect * i), size, i * numCOLLUM + j + 1, "Assets/Inventory/off.png", InventoryBox::State::None);
            }
        }
    } else if (type == Type::Hand) {
        float aspect = 1.f/Config::GetInstance() -> GetAspectRatio();
        for(int i = 0 ; i < numROW; i++) {
            const float offset = 0.005f;
            Boxes[i].resize(numCOLLUM);
            for(int j = 0; j < numCOLLUM; j++) {
                Boxes[i][j] = std::make_shared<InventoryBox>(glm::vec2(position.x + j * size.x - offset * j, position.y - i * size.y + offset / aspect * i), size, i * numCOLLUM + j + 1, "Assets/Inventory/off.png", InventoryBox::State::None);
            }
        }
    } else {
        rightArrow = TextureManager::getInstance() -> getTexture("Assets/Inventory/rightArrow.png");
        if(type == Type::Crafting) {
    
            float aspect = 1.f/ Config::GetInstance() -> GetAspectRatio();
            const float offset = 0.005f;
            for(int i = 0; i < numROW; i++) {
                Boxes[i].resize(numCOLLUM);
                for(int j = 0; j < numCOLLUM; j++) {
                    Boxes[i][j] = std::make_shared<InventoryBox>(glm::vec2(position.x + j * size.x - offset * j, position.y - i * size.y + offset / aspect * i), size, i * numCOLLUM + j + 1, "Assets/Inventory/off.png", InventoryBox::State::None);
                }
            }
    
            glm::vec2 ResultPosition = glm::vec2(position.x + size.x * 3 + offset * 2, position.y - size.y/2.f);
            
            ResultBox = std::make_unique<InventoryBox>(ResultPosition, size, 0, "Assets/Inventory/off.png", InventoryBox::State::None);
            rightArrowPosition =  ResultPosition;
            rightArrowSize = size/1.5f;
            rightArrowPosition.x -= size.x  + offset;
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

    if(type == Type::Crafting) {
        // Check if the formula is match with the recipe
    }
}

void InventorySection::Render() {
    for(int i = 0; i < numROW; i++) {
        for(int j = 0; j < numCOLLUM; j++) {
            Boxes[i][j] -> Render();
        }
    }

    if(ResultBox != nullptr) {
        ResultBox -> Render();
        spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("Screen"));
        spriteRenderer -> DrawSprite(rightArrow, rightArrowPosition, rightArrowSize, 0.f, glm::vec3(1.f), glm::mat4(1.0f), glm::mat4(1.0f));
    }
}

std::shared_ptr<Item> InventorySection::getCursorItem() {
    return cursorItem;
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


bool InventorySection::isActive() {
    return Active;
}

bool InventorySection::Activation() {
    Active ^= 1;
    return Active;
}

void InventorySection::MouseUpdate(const float & xpos, const float & ypos) {
    itemChoose = nullptr;
    cursorItem = nullptr;
    for(int i = 0; i < numROW; i++) {
        bool found = false;
        for(int j = 0; j < numCOLLUM; j++) {
            if(Boxes[i][j] -> isMouseOnBox(xpos, ypos)) {
                Boxes[i][j] -> isChosen();
                itemChoose = Boxes[i][j];
                found = true;
                break;
            }
        }
        if(found) break;
    }
}


void InventorySection::PickItem() {
    if(itemChoose != nullptr) {
        cursorItem = itemChoose -> getItem();
        if(cursorItem != nullptr) {
            cursorItem -> PickUp();
        }
        itemChoose -> unsetItem();
        itemChoose = nullptr;
    }
}

bool InventorySection::PlaceItem(std::shared_ptr<Item> & item) {
    if(itemChoose == nullptr) return false ;
    if(itemChoose -> isEmpty()) {
        itemChoose -> setItem(item);
        item = nullptr;
        return true;
    }

    if(itemChoose -> getItem() -> getID() == item -> getID()) {
        int left = itemChoose -> getItem() -> addNumber(item -> getNumber());
        if(left != 0) {
            item -> addNumber(- (item -> getNumber() - left));
            return false;
        }else {
            item = nullptr;
            return true;
        }
    }else {
        std::shared_ptr<Item> temp = itemChoose -> getItem();
        itemChoose -> setItem(item);
        item = temp;
        return true;
    }
    return false;
}

bool InventorySection:: PlaceItem(std::shared_ptr<Item> & item, bool one) {
    if(itemChoose == nullptr) return false ;
    if(itemChoose -> isEmpty()) {
        int old = item -> getNumber();
        item -> addNumber(-item -> getNumber() + 1);
        std::shared_ptr <Item> temp = nullptr;
        temp = item -> clone();
        itemChoose -> setItem(temp);
        item -> addNumber(old -2);
        if(item -> getNumber() == 0) {
            item = nullptr;
        }

        return true;
    }

    if(itemChoose -> getItem() -> getID() == item -> getID()) {
        
        int left = itemChoose -> getItem() -> addNumber(1);
        item -> addNumber(-1);
        if(left != 0) {
            item -> addNumber(1);
            return false;
        }else if(item -> getNumber() == 0) {
            item = nullptr;
        }
        return true;
    }
    
    return false;
}

