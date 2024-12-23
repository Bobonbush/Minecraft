#include "ItemConst.h"

std::map<int , ItemConst::Type> ItemConst::itemMap;
std::map<int ,float> ItemConst::itemEfficiency;
std::map<int ,int > ItemConst :: ItemDrop;
std::map<int ,glm::vec2 > ItemConst :: RequiredTool;
std::map<int ,int > ItemConst :: Armor_Value;
std::map<int ,int > ItemConst :: MaxUse;


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

    itemMap[static_cast<int>(ItemID::Stick)] = Type::Consumable;

    itemMap[static_cast<int>(ItemID::Iron)] = Type::Mineral;
    itemMap[static_cast<int>(ItemID::Copper)] = Type::Mineral;
    itemMap[static_cast<int>(ItemID::Laser)] = Type::Mineral;
    itemMap[static_cast<int>(ItemID::Blue)] = Type::Mineral;
    itemMap[static_cast<int>(ItemID::Coal)] = Type::Mineral;

    itemMap[static_cast<int>(ItemID::Apple)] = Type::Food;
    itemMap[static_cast<int>(ItemID::GoldenApple)] = Type::Food;

    itemEfficiency[static_cast<int>(ItemID::Iron_Sword)] = 0.0f;
    itemEfficiency[static_cast<int>(ItemID::Copper_Sword)] = 0.0f;
    itemEfficiency[static_cast<int>(ItemID::Laser_Sword)] = 0.0f;
    itemEfficiency[static_cast<int>(ItemID::Blue_Sword)] = 0.0f;

    itemEfficiency[static_cast<int>(ItemID::Bow)] = 0.0f;
    itemEfficiency[static_cast<int>(ItemID::Arrow)] = 0.0f;

    itemEfficiency[static_cast<int>(ItemID::Iron_Pickage)] = 1.0f;
    itemEfficiency[static_cast<int>(ItemID::Copper_Pickage)] = 2.0f;
    itemEfficiency[static_cast<int>(ItemID::Laser_Pickage)] = 3.0f;
    itemEfficiency[static_cast<int>(ItemID::Blue_Pickage)] = 4.0f;

    itemEfficiency[static_cast<int>(ItemID::Iron_Axe)] = 1.0f;
    itemEfficiency[static_cast<int>(ItemID::Copper_Axe)] = 2.0f;
    itemEfficiency[static_cast<int>(ItemID::Laser_Axe)] = 3.0f;
    itemEfficiency[static_cast<int>(ItemID::Blue_Axe)] = 4.0f;

    initRequiredTool();
    initItemDropMap();
    initArmorValue();
    initMaxUse();


}

void ItemConst::initMaxUse() {
    MaxUse[(int)ItemID::Iron_Sword] = 20;
    MaxUse[(int)ItemID::Copper_Sword] = 40;
    MaxUse[(int)ItemID::Laser_Sword] = 80;
    MaxUse[(int)ItemID::Blue_Sword] = 160;

    MaxUse[(int)ItemID::Iron_Axe] = 20;
    MaxUse[(int)ItemID::Copper_Axe] = 40;
    MaxUse[(int)ItemID::Laser_Axe] = 80;
    MaxUse[(int)ItemID::Blue_Axe] = 160;

    MaxUse[(int)ItemID::Iron_Pickage] = 2;
    MaxUse[(int)ItemID::Copper_Pickage] = 40;
    MaxUse[(int)ItemID::Laser_Pickage] = 80;
    MaxUse[(int)ItemID::Blue_Pickage] = 160;


}


void ItemConst::initRequiredTool() {
    RequiredTool[(int)BLOCKID::Grass] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Dirt] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Stone] = glm::vec2(ItemID::Iron_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::Wood] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::CraftingTable] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Water] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Sand] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Bedrock] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::Leaf] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::TearWood] = glm::vec2(-1, ItemID::TOTAL);
    RequiredTool[(int)BLOCKID::BlueOre] = glm::vec2(ItemID::Laser_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::CopperOre] = glm::vec2(ItemID::Iron_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::LaserOre] = glm::vec2(ItemID::Blue_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::CoalOre] = glm::vec2(ItemID::Iron_Pickage, ItemID::Blue_Pickage);
    
    RequiredTool[(int)BLOCKID::SpecialLeaf] = glm::vec2(ItemID::Laser_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::SpecialWood] = glm::vec2(ItemID::Blue_Pickage, ItemID::Blue_Pickage);
    RequiredTool[(int)BLOCKID::Cactus] = glm::vec2(-1, ItemID::TOTAL);
}

void ItemConst::initItemDropMap() {
    ItemDrop[(int)BLOCKID::Grass] = static_cast<int>(BLOCKID::Dirt);
    ItemDrop[(int)BLOCKID::Dirt] = static_cast<int>(BLOCKID::Dirt);
    ItemDrop[(int)BLOCKID::Stone] = static_cast<int>(BLOCKID::Stone);
    ItemDrop[(int)BLOCKID::Wood] = static_cast<int>(BLOCKID::Wood);
    ItemDrop[(int)BLOCKID::CraftingTable] = static_cast<int>(BLOCKID::CraftingTable);
    ItemDrop[(int)BLOCKID::Water] = 0;
    ItemDrop[(int)BLOCKID::Sand] = static_cast<int>(BLOCKID::Sand);
    ItemDrop[(int)BLOCKID::Bedrock] = static_cast<int>(BLOCKID::Bedrock);
    ItemDrop[(int)BLOCKID::BlueOre] = static_cast<int>(ItemID::Blue);
    ItemDrop[(int)BLOCKID::CopperOre] = static_cast<int>(ItemID::Copper);
    ItemDrop[(int)BLOCKID::LaserOre] = static_cast<int>(ItemID::Laser);
    ItemDrop[(int)BLOCKID::CoalOre] = static_cast<int>(ItemID::Coal);
    ItemDrop[(int)BLOCKID::Leaf] = static_cast<int>(ItemID::Apple);
    ItemDrop[(int)BLOCKID::TearWood] = static_cast<int>(BLOCKID::TearWood);
    ItemDrop[(int)BLOCKID::SpecialLeaf] = static_cast<int>(ItemID::GoldenApple);
    ItemDrop[(int)BLOCKID::SpecialWood] = static_cast<int>(BLOCKID::SpecialWood);
    ItemDrop[(int)BLOCKID::Cactus] = static_cast<int>(BLOCKID::Cactus);


}

void ItemConst::initArmorValue() {
    Armor_Value[(int)ItemID::Iron_Helmet] = 1;
    Armor_Value[(int)ItemID::Copper_Helmet] = 2;
    Armor_Value[(int)ItemID::Laser_Helmet] = 2;
    Armor_Value[(int)ItemID::Blue_Helmet] = 2;

    Armor_Value[(int)ItemID::Iron_Chestplate] = 2;
    Armor_Value[(int)ItemID::Copper_Chestplate] = 3;
    Armor_Value[(int)ItemID::Laser_Chestplate] = 3;
    Armor_Value[(int)ItemID::Blue_Chestplate] = 4;

    Armor_Value[(int)ItemID::Iron_Leggings] = 1;
    Armor_Value[(int)ItemID::Copper_Leggings] = 2;
    Armor_Value[(int)ItemID::Laser_Leggings] = 1;
    Armor_Value[(int)ItemID::Blue_Leggings] = 2;

    Armor_Value[(int)ItemID::Iron_Boots] = 1;
    Armor_Value[(int)ItemID::Copper_Boots] = 1;
    Armor_Value[(int)ItemID::Laser_Boots] = 2;
    Armor_Value[(int)ItemID::Blue_Boots] = 2;


}

const int ItemConst::getToolMaxUse(const int & id) {
    return MaxUse[id];
}

const int ItemConst::getArmorValue(const int & id) {
    return Armor_Value[id];
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

const float ItemConst::getItemEfficiency(const int &id) {
    return itemEfficiency[id];
}

const bool ItemConst::validTool(const int & blockID, const int & itemID)  {
    if(RequiredTool[blockID].x == -1) return true;
    if(RequiredTool[blockID].x <= itemID && RequiredTool[blockID].y >= itemID) {
        return true;
    }
    return false;
}

const glm::vec2 ItemConst::getRequiredTool(const int & ID) {
    return RequiredTool[ID];
}

const int ItemConst::getItemDrop(const int & ID) {
    return ItemDrop[ID];
}

const bool ItemConst::validEfficiency(const int & id, const  int& blockID) {
    if((BLOCKID)blockID == BLOCKID::Wood || (BLOCKID)blockID == BLOCKID::CraftingTable || (BLOCKID) blockID == BLOCKID::TearWood) {
        if(id >= (int)ItemID::Iron_Axe && id <= (int)ItemID::Blue_Axe) {
            return true;
        }
        return false;            
    }

    if((BLOCKID)blockID == BLOCKID::Stone || (BLOCKID)blockID == BLOCKID::BlueOre || (BLOCKID)blockID == BLOCKID::CopperOre || (BLOCKID)blockID == BLOCKID::LaserOre || (BLOCKID)blockID == BLOCKID::CoalOre) {
        if(id >= (int)ItemID::Iron_Pickage && id <= (int)ItemID::Blue_Pickage) {
            return true;
        }
        return false;
    }

    return false;
            
}

const ItemConst::Type ItemConst::getItemType(const int & id) {
    return itemMap[id];
}