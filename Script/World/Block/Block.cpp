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

    blockHardness[static_cast<int>(BLOCKID::Air)] = 0;
    blockHardness[static_cast<int>(BLOCKID::Grass)] = 1.5;
    blockHardness[static_cast<int>(BLOCKID::Dirt)] = 1.5;
    blockHardness[static_cast<int>(BLOCKID::Stone)] = 3.f;
    blockHardness[static_cast<int>(BLOCKID::Wood)] = 2.f;
    


    for(auto & block : blockMap) {
        blockMapReverse[block.second] = block.first;
    }
}


const float Block::GetBlockHardness(int id) {
    return Block::blockHardness[id];
}




