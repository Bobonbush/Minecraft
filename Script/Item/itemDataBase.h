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
        std::string getItemName(ItemID id);

        TextureAtlas textureAtlas;
};

#endif // ITEMDATABASE_H


