#ifndef BIOME_H
#define BIOME_H
#include "Chunk/ChunkSection.h"
#include "Maths/FastNoise.h"

class Biome {
    protected : 
        float water_min;
        float water_max;

        float surface = 100;

        float slope = 80.f;

        std::vector<BLOCKID> blocks;

        FastNoise noise;
    
    public :
        Biome() = default;
        
        virtual BLOCKID getBlocks(int x, int y ,int z) = 0;

        void setFastNoise(const FastNoise &noise) {
            this -> noise = noise;
        }
    
};

#endif