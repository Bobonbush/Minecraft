#include "ItemDatabase.h"

ItemDataBase * ItemDataBase::instance = nullptr;

ItemDataBase::ItemDataBase() : textureAtlas("Assets/items/items.png") {
    //items[(unsigned) ItemID::Sword] = std::make_unique<ItemData>("Sword");

    
    initItemMap();
}

void ItemDataBase::initItemMap() {
    itemMap[ItemID::Sword] = "Sword";
}


ItemDataBase::~ItemDataBase() {
    delete instance;
}

std::string ItemDataBase::getItemName(ItemID id) {
    return itemMap[id];
}

const ItemData & ItemDataBase::getData(ItemID id) const {
    return *items[(unsigned) id];
}
