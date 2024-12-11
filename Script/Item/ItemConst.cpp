#include "ItemConst.h"

std::map<int , ItemConst::Type> ItemConst::itemMap;


void ItemConst::initBlockMap() {
    
    itemMap[static_cast<int>(ItemID::Sword)] = Type::Weapon;
    
}