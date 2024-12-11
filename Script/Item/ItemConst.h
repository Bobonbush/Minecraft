
#ifndef ITEMCONST_H
#define ITEMCONST_H
#include "Block/Block.h"


enum class ItemID : int {

    // There won't be any iron, just stone things  and copper things , and a special laser and blue things
    Iron_Sword = BLOCKID::TOTAL,
    Copper_Sword,
    Laser_Sword,
    Blue_Sword,

    Bow,
    Arrow,

    Iron_Pickage,
    Copper_Pickage,
    Laser_Pickage,
    Blue_Pickage,

    Iron_Axe,
    Copper_Axe,
    Laser_Axe,
    Blue_Axe,

    Iron_Helmet,
    Copper_Helmet,
    Laser_Helmet,
    Blue_Helmet,

    Iron_Chestplate,
    Copper_Chestplate,
    Laser_Chestplate,
    Blue_Chestplate,

    Iron_Leggings,
    Copper_Leggings,
    Laser_Leggings,
    Blue_Leggings,

    Iron_Boots,
    Copper_Boots,
    Laser_Boots,
    Blue_Boots,

    Stick,

    Iron,
    Copper,
    Laser,
    Blue,
    
    TOTAL,
};

class ItemConst {

    

    public :

        enum class Type {
            Weapon = 1,
            Armor = 2,
            Consumable = 3,
            Mineral = 4,
            Tool = 5
        };
        static std::map<int , Type> itemMap;

        static void initBlockMap();

        static int getMaxStack( ItemID & id);
};



#endif // ITEMCONST_H