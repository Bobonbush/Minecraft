#include "ItemDatabase.h"

ItemDataBase * ItemDataBase::instance = nullptr;

ItemDataBase::ItemDataBase() : textureAtlas("Assets/items/items.png") {
    items[(unsigned) ItemID::Sword - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Sword");
    items[(unsigned) ItemID::Bow - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Bow");
    items[(unsigned) ItemID::Arrow - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Arrow");
    items[(unsigned) ItemID::Pickage - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Pickage");
    items[(unsigned) ItemID::Axe - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Axe");

    
    initItemMap();
}

void ItemDataBase::initItemMap() {
    itemMap[ItemID::Sword] = "Sword";
    itemMap[ItemID::Bow] = "Bow";
    itemMap[ItemID::Arrow] = "Arrow";
    itemMap[ItemID::Pickage] = "Pickage";
    itemMap[ItemID::Axe] = "Axe";
    
}


ItemDataBase::~ItemDataBase() {
    delete instance;
}

std::string ItemDataBase::getItemName(ItemID id) {
    return itemMap[id ];
}

const ItemData & ItemDataBase::getData(ItemID id) const {
    return *items[(unsigned) id - (unsigned) BLOCKID::TOTAL];
}
