#include "ChunkBlock.h"

ChunkBlock::ChunkBlock(BLOCKID id) : id((int) id) {
    if(id == BLOCKID::Air || id == BLOCKID::Water) {
        Opaque = true;
    }
}

const BlockData& ChunkBlock::getData() const {
    return BlockDataBase::GetInstance() -> getData((BLOCKID) id);
}

const BlockType& ChunkBlock::getType() const {
    return BlockDataBase::GetInstance() -> getBlock((BLOCKID) id);
}

bool ChunkBlock::operator == (const ChunkBlock & another) const {
    return id == another.id;
}

bool ChunkBlock::operator!=(const ChunkBlock & another) const {
    return id != another.id;
}

bool ChunkBlock::isOpaque() const {
    return Opaque;
}