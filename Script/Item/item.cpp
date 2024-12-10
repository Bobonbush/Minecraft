#include "item.h"

Item::Item() : stats({0}) {
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


