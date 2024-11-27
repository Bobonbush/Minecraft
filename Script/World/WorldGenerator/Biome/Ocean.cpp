#include "Ocean.h"

BLOCKID Ocean::getBlocks(int x, int y, int z) {
    float noise = this -> noise.GetNoise(x, z);
    if(y > water_max) return BLOCKID::Air;

    if(y < water_min) {
        if(water_min + noise * 20.f < y) {
            return BLOCKID::Sand;
        } else if(water_min + noise * 40.f < y) {
            return BLOCKID::Dirt;
        }else {
            return BLOCKID::Stone;
        }
    }

    return BLOCKID::Water;
}