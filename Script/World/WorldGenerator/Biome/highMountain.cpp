#include "highMountain.h"


BLOCKID highMountain::getBlocks(int x, int y, int z) {
    
    float noise = this -> noise.GetNoise(x, z);

    if(surface + noise * slope/10 > y) {
        return BLOCKID::Stone;
    }
    if(surface + noise * slope > y) {
        return BLOCKID::Stone;
    }

    
    
    if(y < water_min) {
        if(water_min + noise * 20.f < y) {
            return BLOCKID::Sand;
        } else if(water_min + noise * 40.f < y) {
            return BLOCKID::Dirt;
        }else {
            return BLOCKID::Stone;
        }
    }
    if(y < water_max) {
        return BLOCKID::Water;
    }

    if(y == 0) {
        return BLOCKID::Bedrock;
    }
    
    return BLOCKID::Air;
}
