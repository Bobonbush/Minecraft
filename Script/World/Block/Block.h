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
};


enum class BLOCKID : int {
    Air = 0,
    Grass = 1,
    Dirt = 2,
    Stone = 3,

    TOTAL,
};

#endif 