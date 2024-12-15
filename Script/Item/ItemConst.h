
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
    Coal,

    Apple,
    GoldenApple,
    
    TOTAL,
};

class ItemConst {

    

    public :

        enum class Type {
            Weapon = 1,
            Armor = 2,
            Consumable = 3,
            Mineral = 4,
            Tool = 5,
            Food = 6,
        };
        static std::map<int , Type> itemMap;
        static std::map<int , float> itemEfficiency;   // Default Item = 0
        static std::map<int ,int> ItemDrop;
        static std::map<int , glm::vec2> RequiredTool;
        
        static void initBlockMap();
        static void initRequiredTool();
        static void initItemDropMap();

        const static  bool validTool(const int & blockID, const int & itemID);


        const static  glm::vec2 getRequiredTool(const int & ID);
        const static  int getItemDrop(const int & ID);



        static int getMaxStack( ItemID & id);
        static const float getItemEfficiency(const int &id);

        static const bool validEfficiency(const int & id, const  int& blockID);
};



#endif // ITEMCONST_H