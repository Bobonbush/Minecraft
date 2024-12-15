#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#include "Maths/FastNoise.h"
#include "Chunk/ChunkSection.h"
#include "Config.h"
#include "Biome.h"
#include "Algorithm.h"

class NoiseGenerator {
    private:
        FastNoise noise;
        FastNoise biomeNoise;
        FastNoise caveNoise;
        FastNoise ClimateNoise;
        FastNoise materialNoise;
        //std::vector<std::vector<>>
        int waterLevel_min = 60;
        int waterLevel_max = 100;

        std::vector<float> oreProbability = {0.65f, 0.5f, 0.3f, 0.2f};
        std::vector<float> oreMinLevel = {0, 0.03f, 0.03f, 0.1f};
        // coal, copper, laser, blue
        //iron = stone
        std::vector<float> oreMaxLevel = {0.98f, 0.95f, 0.2f, 0.1f};
        float getNoise(float x, float z);
        float getNoise(float x, float y, float z);
    public:
        NoiseGenerator();

        


        

        void BuildChunk(ChunkSection &chunk);

        const bool isOre(float x, float y, float z, float low, float high, int type) const {
            float OreProbability = materialNoise.GetNoise(x, y, z);
            OreProbability = (OreProbability + 1) / 2;

            OreProbability = (1.f - OreProbability * OreProbability);


            //OreProbability *= high / y;
            
            return OreProbability <=  oreProbability[type];
        }
};

#endif