#include "ItemConst.h"

std::map<int , ItemConst::Type> ItemConst::itemMap;


void ItemConst::initBlockMap() {
    
    itemMap[static_cast<int>(ItemID::Sword)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Bow)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Arrow)] = Type::Consumable;
    itemMap[static_cast<int>(ItemID::Pickage)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Axe)] = Type::Weapon;


    
}

int ItemConst::getMaxStack( ItemID & id) {
    if(itemMap[(int)id] == Type::Weapon) {
        return 1;
    }
    if(itemMap[(int)id] == Type::Armor) {
        return 1;
    }
    return 64;
        
}