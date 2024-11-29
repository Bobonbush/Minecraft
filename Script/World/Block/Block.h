#ifndef BLOCK_H
#define BLOCK_H
#include "vector"
#include "Texture.h"

class Block {
    public :
    const static std::vector<GLfloat> Top;
    const static std::vector<GLfloat> Bottom;

    const static std::vector<GLfloat> Left;
    const static std::vector<GLfloat> Right;
    const static std::vector<GLfloat> Front;
    const static std::vector<GLfloat> Back; 

    const static std::vector<GLfloat> upNormal;
    const static std::vector<GLfloat> downNormal;
    const static std::vector<GLfloat> leftNormal;
    const static std::vector<GLfloat> rightNormal;
    const static std::vector<GLfloat> frontNormal;
    const static std::vector<GLfloat> backNormal;

    const static std::vector<glm::vec3> normals;
};


enum class BLOCKID : int {
    Air = 0,
    Grass = 1,
    Dirt = 2,
    Stone = 3,
    CraftingTable = 4,
    Wood = 5,
    Water = 6,
    Sand = 7,
    Bedrock = 8,
    Leaf = 9,

    TOTAL,
};

#endif 