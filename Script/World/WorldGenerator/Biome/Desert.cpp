#include "Desert.h"


BLOCKID Desert::getBlocks(int x, int y, int z) {
    float noise = this -> noise.GetNoise(x, z);
    if(surface + noise * slope > y) {
        return BLOCKID::Sand;
    }

    
    
    if(y < water_min) {
        if(water_min + noise * slope < y) {
            return BLOCKID::Sand;
        } else if(water_min + noise * slope * 2 < y) {
            return BLOCKID::Dirt;
        }else {
            return BLOCKID::Stone;
        }
    }
    if(y < water_max) {
        return BLOCKID::Water;
    }
    
    return BLOCKID::Air;
}