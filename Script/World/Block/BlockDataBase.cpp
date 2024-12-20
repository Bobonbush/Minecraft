#include "BlockDataBase.h"

BlockDataBase * BlockDataBase::instance = nullptr;

BlockDataBase::BlockDataBase() : textureAtlas("Assets/Default pack.png") {
    blocks[(unsigned) BLOCKID::Grass] = std::make_unique<DefaultBlock>("Grass");
    blocks[(unsigned) BLOCKID::Dirt] = std::make_unique<DefaultBlock>("Dirt");
    blocks[(unsigned) BLOCKID::Stone] = std::make_unique<DefaultBlock>("Stone");
    blocks[(unsigned) BLOCKID::Air] = std::make_unique<DefaultBlock>("Air");
    blocks[(unsigned) BLOCKID::CraftingTable] = std::make_unique<DefaultBlock>("Crafting Table");
    blocks[(unsigned) BLOCKID::Wood] = std::make_unique<DefaultBlock>("Wood");
    blocks[(unsigned) BLOCKID::Leaf] = std::make_unique<DefaultBlock>("Leaf");
    blocks[(unsigned) BLOCKID::Sand] = std::make_unique<DefaultBlock>("Sand");
    blocks[(unsigned) BLOCKID::Bedrock] = std::make_unique<DefaultBlock>("Bedrock");
    blocks[(unsigned) BLOCKID::Water] = std::make_unique<DefaultBlock>("Water");
    blocks[(unsigned) BLOCKID::TearWood] = std::make_unique<DefaultBlock>("TearWood");
    blocks[(unsigned) BLOCKID::BlueOre] = std::make_unique<DefaultBlock>("BlueOre");
    blocks[(unsigned) BLOCKID::CopperOre] = std::make_unique<DefaultBlock>("CopperOre");
    blocks[(unsigned) BLOCKID::LaserOre] = std::make_unique<DefaultBlock>("LaserOre");
    blocks[(unsigned) BLOCKID::CoalOre] = std::make_unique<DefaultBlock>("CoalOre");
    blocks[(unsigned) BLOCKID::SpecialLeaf] = std::make_unique<DefaultBlock>("SpecialLeaf");
    blocks[(unsigned) BLOCKID::SpecialWood] = std::make_unique<DefaultBlock>("SpecialWood");
    blocks[(unsigned) BLOCKID::Cactus] = std::make_unique<DefaultBlock>("Cactus");
    blocks[(unsigned) BLOCKID::TNT] = std::make_unique<DefaultBlock>("TNT");

    blocks[(unsigned) BLOCKID::Coal_Block] = std::make_unique<DefaultBlock>("Coal Block");
    blocks[(unsigned) BLOCKID::Copper_Block] = std::make_unique<DefaultBlock>("Copper Block");
    blocks[(unsigned) BLOCKID::Laser_Block] = std::make_unique<DefaultBlock>("Laser Block");
    blocks[(unsigned) BLOCKID::Blue_Block] = std::make_unique<DefaultBlock>("Blue Block"); 

    blocks[(unsigned) BLOCKID::Hand] = std::make_unique<DefaultBlock>("Hand");   
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