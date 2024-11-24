#ifndef HIGHMOUNTAIN_H
#define HIGHMOUNTAIN_H
#include "Biome.h"
#include "Chunk/ChunkSection.h" 



class highMountain : public Biome {
    public:
        highMountain() {
            blocks.push_back(BLOCKID::Grass);
            blocks.push_back(BLOCKID::Dirt);
            blocks.push_back(BLOCKID::Stone);
            blocks.push_back(BLOCKID::Air);
            blocks.push_back(BLOCKID::Wood);
            blocks.push_back(BLOCKID::Sand);
            blocks.push_back(BLOCKID::Bedrock);
            blocks.push_back(BLOCKID::Water);

            surface = 98;
            slope = 180.f;

            water_min = 84;
            water_max = 90;
        }

        virtual BLOCKID getBlocks(int x, int y, int z) override;
};

#endif