#include "Block.h"

const std::vector<GLfloat> Block::Top = {
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
};


const std::vector<GLfloat> Block::Bottom = {
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
};

const std::vector<GLfloat> Block::Left  = {
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
};

const std::vector<GLfloat> Block::Right = {
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
};

const std::vector<GLfloat> Block::Front = {
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
};

const std::vector<GLfloat> Block::Back = {
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f
};


const std::vector<GLfloat> Block::upNormal = {
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

const std::vector<GLfloat> Block::downNormal = {
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
};

const std::vector<GLfloat> Block::leftNormal = {
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
};

const std::vector<GLfloat> Block::rightNormal = {
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
};

const std::vector<GLfloat> Block::frontNormal = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

const std::vector<GLfloat> Block::backNormal = {
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
};

const std::vector<glm::vec3> Block::normals = {
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
  
  
    glm::vec3(0.0f, 0.0f, -1.0f)
};


std::map<int , std::string> Block::blockMap;
std::map<std::string , int > Block::blockMapReverse;
std::map<int , float> Block::blockHardness;

void Block::initBlockMap() {
    blockMap[static_cast<int>(BLOCKID::Air)] = "Air";
    blockMap[static_cast<int>(BLOCKID::Grass)] = "Grass";
    blockMap[static_cast<int>(BLOCKID::Dirt)] = "Dirt";
    blockMap[static_cast<int>(BLOCKID::Stone)] = "Stone";
    blockMap[static_cast<int>(BLOCKID::CraftingTable)] = "Crafting Table";
    blockMap[static_cast<int>(BLOCKID::Wood)] = "Wood";
    blockMap[static_cast<int>(BLOCKID::Water)] = "Water";
    blockMap[static_cast<int>(BLOCKID::Sand)] = "Sand";
    blockMap[static_cast<int>(BLOCKID::Bedrock)] = "Bedrock";
    blockMap[static_cast<int>(BLOCKID::Leaf)] = "Leaf";
    blockMap[static_cast<int>(BLOCKID::TearWood)] = "TearWood";
    blockMap[static_cast<int>(BLOCKID::BlueOre)] = "BlueOre";
    blockMap[static_cast<int>(BLOCKID::CopperOre)] = "CopperOre";
    blockMap[static_cast<int>(BLOCKID::LaserOre)] = "LaserOre";
    blockMap[static_cast<int>(BLOCKID::CoalOre)] = "CoalOre";
    blockMap[static_cast<int>(BLOCKID::SpecialWood)] = "SpecialWood";
    blockMap[static_cast<int>(BLOCKID::SpecialLeaf)] = "SpecialLeaf";
    blockMap[static_cast<int>(BLOCKID::Cactus)] = "Cactus";
    blockMap[static_cast<int>(BLOCKID::TNT)] = "TNT";
    blockMap[static_cast<int>(BLOCKID::TNT_Active)] = "TNT_Active";

    blockMap[static_cast<int>(BLOCKID::Coal_Block)] = "Coal Block";
    blockMap[static_cast<int>(BLOCKID::Copper_Block)] = "Copper Block";
    blockMap[static_cast<int>(BLOCKID::Laser_Block)] = "Laser Block";
    blockMap[static_cast<int>(BLOCKID::Blue_Block)] = "Blue Block";

    blockMap[static_cast<int>(BLOCKID::Hand)] = "Hand";

    


    for(auto & block : blockMap) {
        blockMapReverse[block.second] = block.first;
    }

    initBlockHardness();
}
void Block::initBlockHardness() {

    blockHardness[static_cast<int>(BLOCKID::Air)] = 0;
    blockHardness[static_cast<int>(BLOCKID::Grass)] = 1.;
    blockHardness[static_cast<int>(BLOCKID::Dirt)] = 1.;
    blockHardness[static_cast<int>(BLOCKID::Stone)] = 3.f;
    blockHardness[static_cast<int>(BLOCKID::Wood)] = 2.f;
    blockHardness[static_cast<int>(BLOCKID::CraftingTable)] = 2.f;
    blockHardness[static_cast<int>(BLOCKID::Water)] = 0.f;
    blockHardness[static_cast<int>(BLOCKID::Sand)] = 1.5;
    blockHardness[static_cast<int>(BLOCKID::Bedrock)] = 1000000.f;
    blockHardness[static_cast<int>(BLOCKID::Leaf)] = 0.5;
    blockHardness[static_cast<int>(BLOCKID::TearWood)] = 2.f;
    blockHardness[static_cast<int>(BLOCKID::BlueOre)] = 15.f;
    blockHardness[static_cast<int>(BLOCKID::CopperOre)] = 5.f;
    blockHardness[static_cast<int>(BLOCKID::LaserOre)] = 10.f;
    blockHardness[static_cast<int>(BLOCKID::CoalOre)] = 3.f;
    blockHardness[static_cast<int>(BLOCKID::SpecialWood)] = 15.f;
    blockHardness[static_cast<int>(BLOCKID::SpecialLeaf)] = 15.5;
    blockHardness[static_cast<int>(BLOCKID::Cactus)] = 1.5;
    blockHardness[static_cast<int>(BLOCKID::TNT)] = 0.f;
    blockHardness[static_cast<int>(BLOCKID::TNT_Active)] = 1000000.f;
    blockHardness[static_cast<int>(BLOCKID::Coal_Block)] = 3.f;
    blockHardness[static_cast<int>(BLOCKID::Copper_Block)] = 5.f;
    blockHardness[static_cast<int>(BLOCKID::Laser_Block)] = 10.f;
    blockHardness[static_cast<int>(BLOCKID::Blue_Block)] = 15.f;
}


const float Block::GetBlockHardness(int id) {
    return Block::blockHardness[id];
}




