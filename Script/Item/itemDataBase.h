#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H
#include "Texture&Shader/TextureAtlas.h"
#include "itemData.h"
#include "ItemConst.h"
#include <map>


class ItemDataBase : public Singleton {
    private:
        ItemDataBase();
        static ItemDataBase * instance;

        void initItemMap();

        std::array<std::unique_ptr<ItemData>, (unsigned) ItemID::TOTAL - (unsigned)BLOCKID::TOTAL >  items;
        std::map<ItemID, std::string> itemMap;  
        std::map<std::string , int> ReverseitemMap;
        
    public:
        static ItemDataBase * GetInstance() {
            if(instance == nullptr) {
                instance = new ItemDataBase();
                ItemConst::initBlockMap();
            }

            return instance;
        }

        ~ItemDataBase();

        const ItemData & getData(ItemID id) const;
        const std::string getItemName(int id);
        int getItemID(const std::string & name);

        TextureAtlas textureAtlas;
        TextureAtlas MineralAtlas;

        
};

#endif // ITEMDATABASE_H


