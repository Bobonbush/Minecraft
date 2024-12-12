#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#include "Maths/FastNoise.h"
#include "Chunk/ChunkSection.h"

class NoiseGenerator {
    private:
        FastNoise noise;
        FastNoise biomeNoise;
        FastNoise caveNoise;
        FastNoise ClimateNoise;
        //std::vector<std::vector<>>
        float waterSurface = 0.5f;
    public:
        NoiseGenerator() {
            

            // Biome Noise
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(3);
            noise.SetFrequency(0.0015);
            noise.SetFractalGain(0.5);
            noise.SetFractalLacunarity(1.8);
            noise.SetFractalType(FastNoise::RigidMulti);
           
            noise.SetSeed(1337);

            // Biome Noise
            biomeNoise.SetNoiseType(FastNoise::SimplexFractal);
            biomeNoise.SetFractalOctaves(3);
            biomeNoise.SetFrequency(0.005);
            biomeNoise.SetFractalGain(0.5);
            biomeNoise.SetFractalLacunarity(1.8);
            biomeNoise.SetFractalType(FastNoise::RigidMulti);

            biomeNoise.SetSeed(1337);

            caveNoise.SetNoiseType(FastNoise::SimplexFractal);
            caveNoise.SetFractalOctaves(3);
            caveNoise.SetFrequency(0.025);
            caveNoise.SetFractalGain(0.5);
            caveNoise.SetFractalLacunarity(1.8);
            caveNoise.SetFractalType(FastNoise::RigidMulti);

            caveNoise.SetSeed(1337);

            ClimateNoise.SetNoiseType(FastNoise::SimplexFractal);
            ClimateNoise.SetFractalOctaves(3);
            ClimateNoise.SetFrequency(0.025);
            ClimateNoise.SetFractalGain(0.5);
            ClimateNoise.SetFractalLacunarity(1.8);
            ClimateNoise.SetFractalType(FastNoise::RigidMulti);

            ClimateNoise.SetSeed(1337);

        }

        float getNoise(float x, float z) {
            return noise.GetNoise(x, z);
        }


        float getNoise(float x, float y, float z) {
            return noise.GetNoise(x, y, z);
        }

        void BuildChunk(ChunkSection &chunk , ChunkSection * below) {
            
            for(int x = 0 ; x < Chunk::CHUNK_SIZE ; x++) {
                for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) {
                    float noiseBiome = noise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                    noiseBiome *= biomeNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                    float height = noiseBiome * 100 + 100;
                    for(int y = 0 ; y < Chunk::CHUNK_SIZE ; y++) {
                        BLOCKID id = BLOCKID::Air;
                        float yPos = y + chunk.getPosition().y * Chunk::CHUNK_SIZE;
                        float caveNoises = caveNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, y + chunk.getPosition().y * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                        float climate = ClimateNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                        
                        if(yPos > height || caveNoises < 0.) {
                            //std::cout << yPos << " " << height << '\n';
                            chunk.setBlock(x, y, z, ChunkBlock(id));
                            continue;
                        }

                        
                        id = BLOCKID::Stone;

                        if(y == 0 && chunk.getPosition().y == 0) {
                            id = BLOCKID::Bedrock;
                        }
                        chunk.setBlock(x, y, z, ChunkBlock(id));
                        if(id == BLOCKID::Air) {
                            if(y > 0 && chunk.getBlock(x, y - 1, z) == BLOCKID::Dirt) {
                                chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Grass));
                            }
                            if(below != nullptr && y == 0 && below -> getBlock(x , Chunk::CHUNK_SIZE-1, z) == BLOCKID :: Dirt) {
                                chunk.setBlock(x , y , z , ChunkBlock(BLOCKID::Grass)); 
                            }
                        }
                    }
                }
            }
        }
};

#endif