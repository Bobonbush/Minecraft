#include "Maths/FastNoise.h"
#include "ChunkSection.h"

class NoiseGenerator {
    private:
        FastNoise noise;
        //std::vector<std::vector<>>
        float waterSurface = 0.5f;
    public:
        NoiseGenerator() {
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(4);
            noise.SetFrequency(0.1);
        }

        float getNoise(float x, float z) {
            return noise.GetNoise(x, z);
        }


        float getNoise(float x, float y, float z) {
            return noise.GetNoise(x, y, z);
        }

        void BuildChunk(ChunkSection &chunk) {
            for(int y = 0 ; y < Chunk::CHUNK_HEIGHT ; y++) {
                for(int x = 0 ; x < Chunk::CHUNK_SIZE ; x++) {
                    for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) {
                        float noiseValue = getNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, y + chunk.getPosition().y * Chunk::CHUNK_HEIGHT, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                        noiseValue = (noiseValue + 1) / 2; 
                        //std::cout << noiseValue << std::endl;
                        if( noiseValue < 0.5) {
                            chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Stone));
                        }
                        if(noiseValue < 0.1) {
                            chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Water));
                        }
                        if(noiseValue >= 0.5) {
                            chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Air));
                        }
                    }
                }
            }
        }
};