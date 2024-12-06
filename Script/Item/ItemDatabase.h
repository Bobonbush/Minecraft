#include <Texture.h>
#include <string>
#include "File.h"


class ItemDataHolder {
    public :
        ItemDataHolder() = default;
    glm::vec2 topCoords;
    glm::vec2 sideCoords;
    glm::vec2 bottomCoords;    
} ;

class ItemData {
    private:
        ItemDataHolder itemData;
    public:
        ItemData(const std::string &fileName);
        const ItemDataHolder & getItemData() const;

};

