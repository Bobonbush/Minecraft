
#ifndef ITEMCONST_H
#define ITEMCONST_H
#include "Block/Block.h"


enum class ItemID : int {
    Sword = BLOCKID::TOTAL,
    Bow,
    Arrow,
    Pickage,
    Axe,
    TOTAL,
};

class ItemConst {

    enum class Type {
        Weapon = 1,
        Armor = 2,
        Consumable = 3,
    };

    public :
        static std::map<int , Type> itemMap;

        static void initBlockMap();

        static int getMaxStack( ItemID & id);
};



#endif // ITEMCONST_H