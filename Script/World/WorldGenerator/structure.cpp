#include "structure.h"


Structure::Structure(const float & _frequency, const glm::vec3 & position) : frequency(_frequency), position(position) {
}


Structure::~Structure() {
    blocks.clear();
}


PlainTreeStructure::PlainTreeStructure(const float & _frequency, const glm::vec3 & position) : Structure(_frequency, position) {
    diameter = SPA::RandomInt(2 , 4);
    height = SPA::RandomInt(5 , 8);
    diameter = 2 * diameter + 1;
    BuildVerticalStructure(position.x, position.z, position.y, BLOCKID::Wood);

    for(int i = 0 ; i < diameter /2 ; i++) {
        BuildHorizontalStructure(position.x, position.z, position.y + height - i, BLOCKID::Leaf, diameter -(diameter / 2 - i) * 2);
    }
}

PlainTreeStructure::~PlainTreeStructure() {
    blocks.clear();
}

void Structure::BuildVerticalStructure(const float &x , const float &z, const float &y, const BLOCKID &block) {
    for(int i = 0 ; i < height ; i++) {
        blocks.push_back(std::make_pair(glm::vec3(x, y + i, z), block));
    }
}

void Structure::BuildHorizontalStructure(const float &x , const float &z, const float &y, const BLOCKID &block, const float &dia) {
    float radius = dia / 2.f;
    for(int i = -radius ; i <= radius ; i++) {
        for(int j = -radius ; j <= radius ; j++) {
            bool exists = false;
            for(int z = 0 ; z < (int)blocks.size() ; z++) {
                if(blocks[z].first == glm::vec3(x + i, y, z + j)) {
                    exists = true;
                    break;
                }
            }
            if(exists) {
                continue;
            }
            blocks.push_back(std::make_pair(glm::vec3(x + i, y, z + j), block));
        }
    }
}

CactusStructure::CactusStructure(const float & _frequency, const glm::vec3 & position) : Structure(_frequency, position) {
    height = SPA::RandomInt(3, 5);
    BuildVerticalStructure(position.x, position.z, position.y, BLOCKID::Cactus);
}

CactusStructure::~CactusStructure() {
    blocks.clear();
}

SpecialTreeStructure::SpecialTreeStructure(const float & _frequency, const glm::vec3 & position) : Structure(_frequency, position) {
    diameter = SPA::RandomInt(4 , 6);
    height = SPA::RandomInt(14 , 16);
    diameter = 2 * diameter + 1;
    BuildVerticalStructure(position.x, position.z, position.y, BLOCKID::SpecialWood);

    for(int i = 0 ; i < diameter /2 ; i++) {
        BuildHorizontalStructure(position.x, position.z, position.y + height - i, BLOCKID::SpecialLeaf, diameter -(diameter / 2 - i) * 2);
    }
}

SpecialTreeStructure::~SpecialTreeStructure() {
    blocks.clear();
}





