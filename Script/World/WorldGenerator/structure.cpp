#include "structure.h"


Structure::Structure(const float & _frequency, const glm::vec3 & position) : frequency(_frequency), position(position) {
}


Structure::~Structure() {
    blocks.clear();
}


PlainTreeStructure::PlainTreeStructure(const float & _frequency, const glm::vec3 & position) : Structure(_frequency, position) {
    diameter = SPA::RandomInt(1 , 3);
    height = SPA::RandomInt(4 , 7);


    blocks = std::vector<std::vector<std::vector<BLOCKID>>>(height, std::vector<std::vector<BLOCKID>>(diameter * 2, std::vector<BLOCKID>(diameter * 2, BLOCKID::Air)));
    int middle = (diameter + 1) /2 - 1;
    for(int y = 0 ; y < height ; y++) {
        blocks[y][middle][middle] = BLOCKID::Wood;
    }

    for(int y = height -1 ; y >= height - diameter ; y-- ) {
        blocks[y][middle][middle] = BLOCKID::Leaf;
    }

    for(int y = height-1 ; y >= height - diameter ; y--) {
        for(int x = 0 ; x < diameter * 2 ; x++) {
            for(int z = 0 ; z < diameter * 2 ; z++) {
                if(x == middle && z == middle) {
                    continue;
                }
                if(glm::distance(glm::vec2(x, z), glm::vec2(middle, middle)) < diameter) {
                    blocks[y][x][z] = BLOCKID::Leaf;
                }
            }
        }
    }

    this -> position.x -= diameter /2.f;
    this -> position.z -= diameter /2.f;
}

PlainTreeStructure::~PlainTreeStructure() {
    blocks.clear();
}

BLOCKID PlainTreeStructure::SetBlock(float x, float y, float z) {
    int indexY = y - position.y;
    int indexX = x - position.x;
    int indexZ = z - position.z;
    if(indexY < 0 || indexY >= blocks.size() || indexX < 0 || indexX >= blocks[0].size() || indexZ < 0 || indexZ >= blocks[0][0].size()) {
        return BLOCKID::Air;
    }

    return blocks[indexY][indexX][indexZ];
}




