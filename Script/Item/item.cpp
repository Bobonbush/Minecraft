#include "item.h"

Item::Item(int number) : stats({number}) {
}

Item::~Item() {
}

BlockItem::BlockItem(BLOCKID id, int number,const std::string& name) : Item(number), data(name) {
    
    cubeRenderer = CubeRenderer::getInstance();

    type = "Block";

    BlockDataBase * blockDataBase = BlockDataBase::GetInstance();
    data = blockDataBase -> getData(id);

    stats.id = id;
    stats.number = number;
}

BlockItem::~BlockItem() {
}

void BlockItem::Render() {
    glm::vec2 top = data.getBlockData().topCoords;
    glm::vec2 side = data.getBlockData().sideCoords;
    glm::vec2 bottom = data.getBlockData().bottomCoords;   
    cubeRenderer -> LoadData(top, side, bottom);
    cubeRenderer -> add(position);
    
    glm::vec3 size = glm::vec3(0.05f);
    size.y *= Config:: GetInstance() -> GetAspectRatio();
    
    cubeRenderer -> renderCubes(glm::mat4(1.0f), glm::mat4(1.0f), size);
    
}

void BlockItem::update() {

}

Item::Stats BlockItem::getStats() {
    return stats;
}

SpriteItem::SpriteItem(const std::string & path, int number) : Item(number) {
    spriteRenderer = SpriteRenderer::getInstance();
}

SpriteItem::~SpriteItem() {
}

void SpriteItem::Render() {
    spriteRenderer -> DrawSprite(texture, glm::vec2(0.f), glm::vec2(0.1f), 0.f, glm::vec3(1.f), glm::mat4(1.0f), glm::mat4(1.0f));
}

void SpriteItem::update() {

}

Item::Stats SpriteItem::getStats() {
    return stats;
}
