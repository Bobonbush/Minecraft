#ifndef BLOCKDATABASE_H
#define BLOCKDATABASE_H
#include "BlockData.h"
#include "Block.h"
#include "Singleton.h"
#include "BlockType.h"
#include "Texture&Shader/TextureAtlas.h"

class BlockDataBase {
    private:
        BlockDataBase();
        static BlockDataBase * instance;

        std::array<std::unique_ptr<BlockType>, (unsigned) BLOCKID :: TOTAL > blocks;
    public :
        static BlockDataBase * GetInstance() {
            if(instance == nullptr) {
                instance = new BlockDataBase();
            }
            return instance;
        }

        ~BlockDataBase();

        const BlockType & getBlock(BLOCKID id) const;
        const BlockData & getData(BLOCKID id) const;

        TextureAtlas textureAtlas;



        
        
};

#endif // BLOCKDATABASE_H