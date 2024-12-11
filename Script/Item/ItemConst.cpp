#include "ItemConst.h"

std::map<int , ItemConst::Type> ItemConst::itemMap;


void ItemConst::initBlockMap() {
    
    itemMap[static_cast<int>(ItemID::Iron_Sword)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Copper_Sword)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Laser_Sword)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Blue_Sword)] = Type::Weapon;

    itemMap[static_cast<int>(ItemID::Bow)] = Type::Weapon;
    itemMap[static_cast<int>(ItemID::Arrow)] = Type::Consumable;
    
    itemMap[static_cast<int>(ItemID::Iron_Pickage)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Copper_Pickage)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Laser_Pickage)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Blue_Pickage)] = Type::Tool;

    itemMap[static_cast<int>(ItemID::Iron_Axe)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Copper_Axe)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Laser_Axe)] = Type::Tool;
    itemMap[static_cast<int>(ItemID::Blue_Axe)] = Type::Tool;

    itemMap[static_cast<int>(ItemID::Iron_Helmet)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Copper_Helmet)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Laser_Helmet)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Blue_Helmet)] = Type::Armor;

    itemMap[static_cast<int>(ItemID::Iron_Chestplate)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Copper_Chestplate)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Laser_Chestplate)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Blue_Chestplate)] = Type::Armor;

    itemMap[static_cast<int>(ItemID::Iron_Leggings)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Copper_Leggings)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Laser_Leggings)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Blue_Leggings)] = Type::Armor;

    itemMap[static_cast<int>(ItemID::Iron_Boots)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Copper_Boots)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Laser_Boots)] = Type::Armor;
    itemMap[static_cast<int>(ItemID::Blue_Boots)] = Type::Armor;

    itemMap[static_cast<int>(ItemID::Stick)] = Type::Mineral;


}

int ItemConst::getMaxStack( ItemID & id) {
    if(itemMap[(int)id] == Type::Weapon) {
        return 1;
    }
    if(itemMap[(int)id] == Type::Armor) {
        return 1;
    }
    if(itemMap[(int)id] == Type::Tool) {
        return 1;
    }
    return 64;
        
}