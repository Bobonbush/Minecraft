#include "itemModel.h"

ItemModel::ItemModel( const glm::vec3 & scale, int itemID, const std::string & path) : HandModel(scale), itemID(itemID) {
    model = std::make_unique<Model>();
    textureAtlas = std::make_unique<TextureAtlas>(path);
}

ItemModel::~ItemModel() {

}

void ItemModel::render(const glm::mat4 &view, const glm::mat4 & projection) {

}

void ItemModel::update(const float & deltaTime) {

}

int ItemModel::getID() {
    return itemID;
}