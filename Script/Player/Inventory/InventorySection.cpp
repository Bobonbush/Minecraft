#include "InventorySection.h"


CraftingRecipeDataBase * InventorySection::recipe = nullptr;

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
            
            ResultBox = std::make_shared<InventoryBox>(ResultPosition, size, 0, "Assets/Inventory/off.png", InventoryBox::State::None);
            rightArrowPosition =  ResultPosition;
            rightArrowSize = size/1.5f;
            rightArrowPosition.x -= size.x  + offset;
        }

        if(type == Type::CraftingTable) {
            float aspect = 1.f/ Config::GetInstance() -> GetAspectRatio();
            const float offset = 0.005f;
            for(int i = 0; i < numROW; i++) {
                Boxes[i].resize(numCOLLUM);
                for(int j = 0; j < numCOLLUM; j++) {
                    Boxes[i][j] = std::make_shared<InventoryBox>(glm::vec2(position.x + j * size.x - offset * j, position.y - i * size.y + offset / aspect * i), size, i * numCOLLUM + j + 1, "Assets/Inventory/off.png", InventoryBox::State::None);
                }
            }
    
            glm::vec2 ResultPosition = glm::vec2(position.x + size.x * (numROW + 1) + offset * (numROW) , position.y - size.y);
            
            ResultBox = std::make_shared<InventoryBox>(ResultPosition, size, 0, "Assets/Inventory/off.png", InventoryBox::State::None);
            rightArrowPosition =  ResultPosition;
            rightArrowSize = size/1.5f;
            rightArrowPosition.x -= size.x  + offset;
        }

    }

    if(recipe == nullptr) {
        recipe = CraftingRecipeDataBase::GetInstance();
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

    if(ResultBox != nullptr) {
        CreateRecipe();
    }

    if(ResultBox != nullptr) {
        ResultBox -> update();
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
    Active = true;
    return Active;
}

bool InventorySection::Disactivation() {
    Active = false;
    return Active;
}

void InventorySection::MouseUpdate(const float & xpos, const float & ypos) {
    itemChoose = nullptr;
    cursorItem = nullptr;
    isResultBox = false;
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

    if(ResultBox != nullptr) {
        if(ResultBox -> isMouseOnBox(xpos, ypos)) {
            ResultBox -> isChosen();
            itemChoose = ResultBox;
            isResultBox = true;
        }
    }
}


void InventorySection::PickItem() {

    
    if(itemChoose != nullptr) {
        if(isResultBox) {
            cursorItem = ResultBox -> getItem();
            if(cursorItem != nullptr) {
                cursorItem -> PickUp();
            }
            ResultBox -> unsetItem();
            
            int minimal = 0;
            if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                
                for(int i = 0; i < numROW; i++) {
                    for(int j = 0; j < numCOLLUM; j++) {
                        if(Boxes[i][j] -> isEmpty()) {
                            continue;
                        }
                        if(minimal == 0) {
                            minimal = Boxes[i][j] -> getItem() -> getNumber();
                        }else {
                            minimal = SPA::min(minimal, Boxes[i][j] -> getItem() -> getNumber());
                        }
                    }
                }
                
            }else minimal = 1;
            int basicNum = cursorItem -> getNumber();
            int left = cursorItem -> addNumber( (minimal-1) * basicNum);
            left /= basicNum;
            minimal -= left;
            for(int i = 0; i < numROW; i++) {
                for(int j = 0; j < numCOLLUM; j++) {
                    if(Boxes[i][j] -> isEmpty()) {
                        continue;
                    }

                    Boxes[i][j] -> getItem() -> addNumber(-minimal);
                    //std::cout << Boxes[i][j] -> getItem() -> getNumber() << std::endl;
                    if(Boxes[i][j] -> getItem() -> getNumber() == 0) {
                        Boxes[i][j] -> unsetItem();
                    }
                    
                }
            }
            itemChoose -> unsetItem();
            itemChoose = nullptr;
            return ;
        }
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
    if(isResultBox) return false;
    if(type == Type::Weapon) {
        if(ItemConst::getItemType(item -> getID()) != ItemConst::Type::Armor) {
            return false;
        }
    }
    if(itemChoose -> isEmpty()) {
        itemChoose -> setItem(item);
        item = nullptr;
        return true;
    }

    if(itemChoose -> getItem() -> getID() == item -> getID()) {
        int left = itemChoose -> getItem() -> addNumber(item -> getNumber());
        if(type == Type::Crafting) {
            CreateRecipe();
        }
        if(left != 0) {
            item -> addNumber(- (item -> getNumber() - left));
            
            return false;
        }else {
            item = nullptr;
            return true;
        }
    }else {
        std::shared_ptr<Item> temp = itemChoose -> getItem();
        item -> Drop();
        itemChoose -> setItem(item);
        item = temp;
        item -> PickUp();
        return true;
    }
    return false;
}

bool InventorySection:: PlaceItem(std::shared_ptr<Item> & item, bool one) {
    if(itemChoose == nullptr) return false ;
    if(type == Type::Weapon) {
        if(ItemConst::getItemType(item -> getID()) != ItemConst::Type::Armor) {
            return false;
        }
    }
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

void InventorySection::CreateRecipe() {

    

    if(ResultBox == nullptr) return ;
    std::vector<std::vector<int>> matrix(3, std::vector<int>(3, 0));
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            matrix[i][j] = 0;
        }
    }
    
    for(int i = 0; i < numROW; i++) {
        for(int j = 0; j < numCOLLUM; j++) {
            if(Boxes[i][j] -> isEmpty()) {
                matrix[i][j] = 0;
            }else {
                matrix[i][j] = Boxes[i][j] -> getItem() -> getID();
            }
        }
    }

    SPA::ShiftFullyToTopLeft(matrix);
    //std::cout << std::endl;


    std::string result = recipe -> isMatch(matrix);
    
    if(result == "null") {
        ResultBox -> unsetItem();
        return ;
    }
    int number = recipe -> getInstantNumber();

    int id = ItemDataBase::GetInstance() -> getItemID(result);

    std::shared_ptr<Item> item = nullptr;

    if(id < (int) BLOCKID::TOTAL) {
        item = std::make_shared<BlockItem>((BLOCKID) id, ItemDataBase::GetInstance() -> getItemName( id));
    }else {
        item = std::make_shared<SpriteItem>((ItemID) id, ItemDataBase::GetInstance() -> getItemName( id));
    }

    item -> addNumber(number);

    ResultBox -> setItem(item);

    
}

