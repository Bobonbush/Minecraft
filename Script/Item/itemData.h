#ifndef ITEMDATAHOLDER_H
#define ITEMDATAHOLDER_H
#include "Utils/File.h"
#include "Texture.h"
class ItemDataHolder {
    public:
        ItemDataHolder() = default;
    glm::vec2 coords;
        
};

class ItemData {
    public:
        ItemData(const std::string &fileName);
        const ItemDataHolder & getItemData() const;

    private:
    
            ItemDataHolder itemData;
};

#endif // ITEMDATAHOLDER_H