#ifndef CHUNKBLOCK_H
#define CHUNKBLOCK_H
#include "BlockData.h"
#include "BlockDataBase.h"


class ChunkBlock {
    private:
        int id = 1;
        bool Opaque = false;
        bool Water = false;
    public :

    ChunkBlock() = default;
    
    ChunkBlock(BLOCKID id);
    
    const BlockData& getData() const;
    const BlockType& getType() const;

    bool operator == (const ChunkBlock & another) const;
    bool operator != (const ChunkBlock & another) const;
    const BLOCKID getID() const {
        return (BLOCKID) id;
    }

    bool isOpaque() const;
    bool isLiquid() const {
        return Water;
    }
};

#endif // CHUNKBLOCK_H