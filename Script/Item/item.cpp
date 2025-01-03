#include "item.h"


std::unique_ptr<TextHandler> Item::textLoader = nullptr;

Item::Item() : stats({0}) {
    if(textLoader == nullptr) {
        textLoader = std::make_unique<TextHandler>();
        textLoader -> LoadFont("Assets/Font/Revamped.ttf", 12);
    }

    stats.maximalUse = -1;
}


Item::~Item() {
}

BlockItem::BlockItem(BLOCKID id,const std::string& name) : Item(), data(name) {
    
    cubeRenderer = CubeRenderer::getInstance();

    type = "Block";

    BlockDataBase * blockDataBase = BlockDataBase::GetInstance();
    data = blockDataBase -> getData(id);

    stats.id = (int) id;
    stats.number = 0;
}

BlockItem::~BlockItem() {
}

void BlockItem::Render() {
    Config * config = Config::GetInstance();
    int number = stats.number;
    glm::vec2 m_size = Inventory::BoxSize;
    float aspect = 1.f/config -> GetAspectRatio();
    m_size.x *= aspect;
    
    glDisable(GL_DEPTH_TEST);
    if(number > 1)
        textLoader -> RenderMiddleText(SPA::convertNumberToString(number), position.x + m_size.x/3.5f , position.y + m_size.y/3.5f, 1.55f, glm::vec3(0.8f, 0.4f , 0.7f), 0.f, glm::vec2(config -> GetWidth(), config -> GetHeight()));
    glEnable(GL_DEPTH_TEST);
    
    
    glDisable(GL_DEPTH_TEST);
    glm::vec2 top = data.getBlockData().topCoords;
    glm::vec2 side = data.getBlockData().sideCoords;
    glm::vec2 bottom = data.getBlockData().bottomCoords;   
    cubeRenderer -> LoadData(top, side, bottom);
    cubeRenderer -> add(position);
    
    glm::vec3 size = glm::vec3(0.035f);
    size.y *= Config:: GetInstance() -> GetAspectRatio();
    
    cubeRenderer -> renderCubes(glm::mat4(1.0f), glm::mat4(1.0f), size);
    glEnable(GL_DEPTH_TEST);
}

void BlockItem::update() {

}

Item::Stats BlockItem::getStats() {
    return stats;
}

SpriteItem::SpriteItem(ItemID id , const std::string &name) : Item(), data(name) {
    
    quadRenderer = QuadRenderer::getInstance();
    itemDataBase = ItemDataBase::GetInstance();

    type = "Item";

    data = itemDataBase -> getData(id);

    stats.id = (int) id;
    stats.number = 0;

    maxStack = ItemConst::getMaxStack(id);
    limitBar = nullptr;
    if(ItemConst::itemMap[stats.id] == ItemConst::Type::Tool) {
        stats.maximalUse = ItemConst::getToolMaxUse( (int) id);
        limitBar = std::make_unique<LimitBar>(glm::vec2(0.0f, 0.0f), glm::vec2(0.07f, 0.005f), stats.maximalUse);
    }    

}

SpriteItem::~SpriteItem() {
}

void SpriteItem::Render() {
    Config * config = Config::GetInstance();
    int number = stats.number;
    glm::vec2 m_size = Inventory::BoxSize;
    float aspect = 1.f/config -> GetAspectRatio();
    m_size.x *= aspect;

    if(limitBar != nullptr) {
        
        limitBar -> render();
    }

    glDisable(GL_DEPTH_TEST);
    if(number > 1)
        textLoader -> RenderMiddleText(SPA::convertNumberToString(number), position.x + m_size.x/3.5f , position.y + m_size.y/3.5f, 1.55f, glm::vec3(0.8f, 0.4f , 0.7f), 0.f, glm::vec2(config -> GetWidth(), config -> GetHeight()));
    
    glEnable(GL_DEPTH_TEST);

    glm::vec2 coords = data.getItemData().coords;

    if(ItemConst::itemMap[stats.id] == ItemConst::Type::Mineral) {
        quadRenderer -> Mineral = true;
    }else {
        quadRenderer -> Mineral = false;
    }
    
    quadRenderer -> LoadData(coords);
    quadRenderer -> add(position);

    glm::vec3 size = glm::vec3(0.075f);
    size.y *= Config:: GetInstance() -> GetAspectRatio();

    quadRenderer -> renderQuads(glm::mat4(1.0f), glm::mat4(1.0f), size);
    glEnable(GL_DEPTH_TEST);

}

void SpriteItem::update() {
    if(limitBar != nullptr) {
        limitBar -> setCurrent(stats.maximalUse);
    }
}

Item::Stats SpriteItem::getStats() {
    return stats;
}



void SpriteItem::use() {
    
    if(stats.maximalUse == -1) {
        stats.number--;
        return ;
    }
    stats.maximalUse--;

    if(stats.maximalUse == 0) {
        SoundManager::GetInstance() -> PlaySound("ItemBreak");
    }
    
    if(stats.number == 0) {
        stats.id = -1;
    }
}

void SpriteItem::setPosition(const glm::vec3 & position) {
    this -> position = position ;
    if(limitBar != nullptr) {
        limitBar -> setPosition(position + glm::vec3(0.0f , -0.05f, 0.f) );
    }
}