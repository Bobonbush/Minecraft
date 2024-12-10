#include "item.h"


std::unique_ptr<TextHandler> Item::textLoader = nullptr;

Item::Item() : stats({0}) {
    if(textLoader == nullptr) {
        textLoader = std::make_unique<TextHandler>();
        textLoader -> LoadFont("Assets/Font/Revamped.ttf", 12);
    }
}

Item::~Item() {
}

BlockItem::BlockItem(BLOCKID id,const std::string& name) : Item(), data(name) {
    
    cubeRenderer = CubeRenderer::getInstance();

    type = "Block";

    BlockDataBase * blockDataBase = BlockDataBase::GetInstance();
    data = blockDataBase -> getData(id);

    stats.id = id;
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

SpriteItem::SpriteItem(const std::string & path, int number) : Item() {
    spriteRenderer = SpriteRenderer::getInstance();
}

SpriteItem::~SpriteItem() {
}

void SpriteItem::Render() {
    glDisable(GL_DEPTH_TEST);
    spriteRenderer -> DrawSprite(texture, glm::vec2(0.f), glm::vec2(0.1f), 0.f, glm::vec3(1.f), glm::mat4(1.0f), glm::mat4(1.0f));
    glEnable(GL_DEPTH_TEST);
}

void SpriteItem::update() {

}

Item::Stats SpriteItem::getStats() {
    return stats;
}


