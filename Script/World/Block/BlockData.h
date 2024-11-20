#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <Texture.h>
#include <string>
#include "File.h"

class BlockDataHolder {
    public :
        BlockDataHolder() = default;
    glm::vec2 topCoords;
    glm::vec2 sideCoords;
    glm::vec2 bottomCoords;
};
class BlockData {
    public: 
        BlockData(const std::string &fileName);

        const BlockDataHolder & getBlockData() const;

    private :

        BlockDataHolder blockData;
        
} ;

#endif // BLOCKDATA_H