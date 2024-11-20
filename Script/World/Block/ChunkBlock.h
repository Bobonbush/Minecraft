#ifndef CHUNKBLOCK_H
#define CHUNKBLOCK_H
#include "BlockData.h"
#include "BlockDataBase.h"


class ChunkBlock {
    private:
        int id = 1;
    
    public :

    ChunkBlock() = default;
    
    ChunkBlock(BLOCKID id);
    
    const BlockData& getData() const;
    const BlockType& getType() const;

    bool operator == (const ChunkBlock & another) const;

    
};

#endif // CHUNKBLOCK_H