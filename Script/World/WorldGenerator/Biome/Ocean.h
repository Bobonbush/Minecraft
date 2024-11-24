#ifndef OCEAN_H
#define OCEAN_H
#include "Biome.h"
#include "Chunk/ChunkSection.h"

class Ocean : public Biome {
    public : 

    Ocean() {
        blocks.push_back(BLOCKID::Grass);
        blocks.push_back(BLOCKID::Dirt);
        blocks.push_back(BLOCKID::Stone);
        blocks.push_back(BLOCKID::Air);
        blocks.push_back(BLOCKID::Wood);
        blocks.push_back(BLOCKID::Sand);
        blocks.push_back(BLOCKID::Bedrock);
        blocks.push_back(BLOCKID::Water);

        water_min = 44;
        water_max = 90;
    }    

    virtual BLOCKID getBlocks(int x, int y, int z) override;
};

#endif