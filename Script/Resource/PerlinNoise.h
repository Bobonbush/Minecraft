#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>
#include <Texture.h>

namespace Perlin {
    extern std::vector<glm::vec2> gradients;
    int hash(int x, int y);

    glm::vec2 getGradient(int x, int y);


    float fade(float t);

    float lerp(float a, float b, float t);

    float dotGridGradient(int ix, int iy, float x, float y);

    float perlinNoise(float x , float y) ;


}

#endif