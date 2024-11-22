#include "BlockDataBase.h"

BlockDataBase * BlockDataBase::instance = nullptr;

BlockDataBase::BlockDataBase() : textureAtlas("Assets/Default pack.png") {
    blocks[(unsigned) BLOCKID::Grass] = std::make_unique<DefaultBlock>("Grass");
    blocks[(unsigned) BLOCKID::Dirt] = std::make_unique<DefaultBlock>("Dirt");
    blocks[(unsigned) BLOCKID::Stone] = std::make_unique<DefaultBlock>("Stone");
    blocks[(unsigned) BLOCKID::Air] = std::make_unique<DefaultBlock>("Air");
    blocks[(unsigned) BLOCKID::CraftingTable] = std::make_unique<DefaultBlock>("Crafting Table");
    blocks[(unsigned) BLOCKID::Wood] = std::make_unique<DefaultBlock>("Wood");
}

BlockDataBase::~BlockDataBase() {
    delete instance;
}

const BlockType & BlockDataBase::getBlock(BLOCKID id) const {
    return *blocks[(unsigned) id];
}

const BlockData & BlockDataBase::getData(BLOCKID id) const {
    return blocks[(unsigned) id] -> getData();
}