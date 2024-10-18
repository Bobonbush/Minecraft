#include "PerlinNoise.h"

namespace Perlin {
    std::vector<glm::vec2> gradients = {
        glm::vec2(1, 0), glm::vec2(-1, 0), glm::vec2(0, 1), glm::vec2(0, -1),
        glm::vec2(1, 1), glm::vec2(-1, 1), glm::vec2(1, -1), glm::vec2(-1, -1)
    };
    
    
    int hash(int x, int y) {
        return (x * 1619 + y * 31337) & 0x7fffffff;
    }

    glm::vec2 getGradient(int x, int y) {
        return gradients[hash(x, y) % 8];
    }
    
    
    float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

     float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    float dotGridGradient(int ix, int iy, float x, float y) {
        glm::vec2 gradient = getGradient(ix, iy);
        float dx = x - (float)ix;
        float dy = y - (float)iy;
        return (dx * gradient.x + dy * gradient.y);
    }

    float perlinNoise(float x , float y) {

        int x0 = (int)x;
        int x1 = x0 + 1;
        int y0 = (int)y;
        int y1 = y0 + 1;

        float sx = x - (float)x0;
        float sy = y - (float)y0;

        float n0, n1, ix0, ix1, value;

        n0 = dotGridGradient(x0, y0, x, y);
        n1 = dotGridGradient(x1, y0, x, y);
        ix0 = lerp(n0, n1, fade(sx));

        n0 = dotGridGradient(x0, y1, x, y);
        n1 = dotGridGradient(x1, y1, x, y);
        ix1 = lerp(n0, n1, fade(sx));

        value = lerp(ix0, ix1, fade(sy));
        return value;
    }

}
