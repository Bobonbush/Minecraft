#include "ItemDatabase.h"

ItemDataBase * ItemDataBase::instance = nullptr;

ItemDataBase::ItemDataBase() : textureAtlas("Assets/items/items.png"), MineralAtlas("Assets/items/mineral.png") {
    // Item
    MineralAtlas.setIndividualTextureSize(32);
    items[(unsigned) ItemID::Iron_Sword - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Sword");
    items[(unsigned) ItemID::Copper_Sword - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Sword");
    items[(unsigned) ItemID::Laser_Sword - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Sword");
    items[(unsigned) ItemID::Blue_Sword - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Sword");

    items[(unsigned) ItemID::Bow - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Bow");
    items[(unsigned) ItemID::Arrow - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Arrow");

    items[(unsigned) ItemID::Iron_Pickage - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Pickage");
    items[(unsigned) ItemID::Copper_Pickage - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Pickage");
    items[(unsigned) ItemID::Laser_Pickage - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Pickage");
    items[(unsigned) ItemID::Blue_Pickage - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Pickage");

    items[(unsigned) ItemID::Iron_Axe - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Axe");
    items[(unsigned) ItemID::Copper_Axe - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Axe");
    items[(unsigned) ItemID::Laser_Axe - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Axe");
    items[(unsigned) ItemID::Blue_Axe - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Axe");
    
    items[(unsigned) ItemID::Iron_Helmet - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Helmet");
    items[(unsigned) ItemID::Copper_Helmet - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Helmet");
    items[(unsigned) ItemID::Laser_Helmet - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Helmet");
    items[(unsigned) ItemID::Blue_Helmet - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Helmet");

    items[(unsigned) ItemID::Iron_Chestplate - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Chestplate");
    items[(unsigned) ItemID::Copper_Chestplate - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Chestplate");
    items[(unsigned) ItemID::Laser_Chestplate - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Chestplate");
    items[(unsigned) ItemID::Blue_Chestplate - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Chestplate");

    items[(unsigned) ItemID::Iron_Leggings - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Leggings");
    items[(unsigned) ItemID::Copper_Leggings - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Leggings");
    items[(unsigned) ItemID::Laser_Leggings - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Leggings");
    items[(unsigned) ItemID::Blue_Leggings - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Leggings");

    items[(unsigned) ItemID::Iron_Boots - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron_Boots");
    items[(unsigned) ItemID::Copper_Boots - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper_Boots");
    items[(unsigned) ItemID::Laser_Boots - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser_Boots");
    items[(unsigned) ItemID::Blue_Boots - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue_Boots");
    
    items[(unsigned) ItemID::Stick - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Stick");
    
    items[(unsigned) ItemID::Iron - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Iron");
    items[(unsigned) ItemID::Copper - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Copper");
    items[(unsigned) ItemID::Laser - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Laser");
    items[(unsigned) ItemID::Blue - (unsigned) BLOCKID::TOTAL] = std::make_unique<ItemData>("Blue");

    initItemMap();
}

void ItemDataBase::initItemMap() {
    itemMap[ItemID::Iron_Sword] = "Iron_Sword";
    itemMap[ItemID::Copper_Sword] = "Copper_Sword";
    itemMap[ItemID::Laser_Sword] = "Laser_Sword";
    itemMap[ItemID::Blue_Sword] = "Blue_Sword";

    itemMap[ItemID::Bow] = "Bow";
    itemMap[ItemID::Arrow] = "Arrow";
    
    itemMap[ItemID::Iron_Pickage] = "Iron_Pickage";
    itemMap[ItemID::Copper_Pickage] = "Copper_Pickage";
    itemMap[ItemID::Laser_Pickage] = "Laser_Pickage";
    itemMap[ItemID::Blue_Pickage] = "Blue_Pickage";

    itemMap[ItemID::Iron_Axe] = "Iron_Axe";
    itemMap[ItemID::Copper_Axe] = "Copper_Axe";
    itemMap[ItemID::Laser_Axe] = "Laser_Axe";
    itemMap[ItemID::Blue_Axe] = "Blue_Axe";

    itemMap[ItemID::Iron_Helmet] = "Iron_Helmet";
    itemMap[ItemID::Copper_Helmet] = "Copper_Helmet";
    itemMap[ItemID::Laser_Helmet] = "Laser_Helmet";
    itemMap[ItemID::Blue_Helmet] = "Blue_Helmet";

    itemMap[ItemID::Iron_Chestplate] = "Iron_Chestplate";
    itemMap[ItemID::Copper_Chestplate] = "Copper_Chestplate";
    itemMap[ItemID::Laser_Chestplate] = "Laser_Chestplate";
    itemMap[ItemID::Blue_Chestplate] = "Blue_Chestplate";

    itemMap[ItemID::Iron_Leggings] = "Iron_Leggings";
    itemMap[ItemID::Copper_Leggings] = "Copper_Leggings";
    itemMap[ItemID::Laser_Leggings] = "Laser_Leggings";
    itemMap[ItemID::Blue_Leggings] = "Blue_Leggings";

    itemMap[ItemID::Iron_Boots] = "Iron_Boots";
    itemMap[ItemID::Copper_Boots] = "Copper_Boots";
    itemMap[ItemID::Laser_Boots] = "Laser_Boots";
    itemMap[ItemID::Blue_Boots] = "Blue_Boots";

    itemMap[ItemID::Stick] = "Stick";

      
    itemMap[ItemID::Iron] = "Iron";
    itemMap[ItemID::Copper] = "Copper";
    itemMap[ItemID::Laser] = "Laser";
    itemMap[ItemID::Blue] = "Blue";


    for(auto & item : itemMap) {
        ReverseitemMap[item.second] = (int) item.first;
    }
}


ItemDataBase::~ItemDataBase() {
    delete instance;
}

std::string ItemDataBase::getItemName(ItemID id) {
    if((unsigned) id < (unsigned) BLOCKID::TOTAL) {
        return Block::blockMap[(int) id];
    }
    return itemMap[id ];
}

int ItemDataBase::getItemID(const std::string & name) {
    if(Block::blockMapReverse.find(name) != Block::blockMapReverse.end()) {
        return Block::blockMapReverse[name];
    }
    return ReverseitemMap[name];
}

const ItemData & ItemDataBase::getData(ItemID id) const {
    return *items[(unsigned) id - (unsigned) BLOCKID::TOTAL];
}
