#include "Maths/FastNoise.h"
#include "Chunk/ChunkSection.h"
#include "Biome/grassland.h"
#include "Biome/Ocean.h"
#include "Biome/highMountain.h"
#include "Biome/Desert.h"

class NoiseGenerator {
    private:
        FastNoise noise;
        //std::vector<std::vector<>>
        float waterSurface = 0.5f;
        GrassLand grassLand;
        GrassLand grassLandValley;
        Ocean ocean;
        highMountain highMountain;
        Desert desert;
        Desert desertValley;

        void GetBiome();
    public:
        NoiseGenerator() {
            // Biome Noise

            // highMountain
            
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(10);
            noise.SetFrequency(0.15);
            noise.SetFractalGain(2.);
            noise.SetFractalLacunarity(0.75);
            
            noise.SetSeed(15324);

            highMountain.setFastNoise(noise);

            // GrassLand
/*
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(10);
            noise.SetFrequency(0.002);
            noise.SetFractalGain(2.);
            noise.SetFractalLacunarity(1.05);
            noise.SetSeed(15324);
            */
            grassLand.setFastNoise(noise);
            // GrassLand Valley
/*
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(4);
            noise.SetFrequency(0.002);
            noise.SetFractalGain(2.);
            noise.SetFractalLacunarity(0.95);
            noise.SetSeed(15324);
            */
            grassLandValley.setFastNoise(noise);
            // Desert
            
 /*
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(4);
            noise.SetFrequency(0.002);
            noise.SetFractalGain(2.);
            noise.SetFractalLacunarity(1.25);
            noise.SetSeed(15324);
            grassLand.setFastNoise(noise);
            ́*/
            desert.setFastNoise(noise);

            // Desert Valley
            /*
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(10);
            noise.SetFrequency(0.002);
            noise.SetFractalGain(2.);
            noise.SetFractalLacunarity(0.75);
            noise.SetSeed(15324);
            */
            desertValley.setFastNoise(noise);

            

            // Ocean
            /*
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(10);
            noise.SetFrequency(0.1);
            noise.SetFractalGain(1.);
            noise.SetFractalLacunarity(0.5);
            noise.SetSeed(15324);
            */
            ocean.setFastNoise(noise);

            // Biome Noise
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(8);
            noise.SetFrequency(0.0015);
            noise.SetFractalGain(20.);
            noise.SetFractalLacunarity(1.015);
           
            noise.SetSeed(1337);
        }

        float getNoise(float x, float z) {
            return noise.GetNoise(x, z);
        }


        float getNoise(float x, float y, float z) {
            return noise.GetNoise(x, y, z);
        }

        void BuildChunk(ChunkSection &chunk) {
            for(int x = 0 ; x < Chunk::CHUNK_SIZE ; x++) {
                for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) {
                    float noiseBiome = noise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                    Biome * biome = nullptr;
                    noiseBiome = (noiseBiome + 1) / 2;
                    //std::cout << noiseBiome << std::endl;
                    if(noiseBiome < 0.35) {
                        biome = &ocean;
                        //std::cout << "Ocean" << std::endl;
                    }
                    else if(noiseBiome < 0.4) {
                        //std::cout << "Desert" << std::endl;
                        biome = &desert;
                    } else if(noiseBiome < 0.45) {
                        //std::cout << "DesertValley" << std::endl;
                        biome = &desertValley;
                    } else if(noiseBiome < 0.55) {
                        biome = &grassLandValley;
                    }  else if(noiseBiome < 0.8) {
                        //std::cout << "GrassLandValley" << std::endl;
                        
                        biome = &grassLand;
                    }
                    
                     else {
                        biome = &highMountain;
                        //std::cout << "High Mountain" << std::endl;

                    }
                    //biome = &highMountain;
                    
                    for(int y = 0 ; y < Chunk::CHUNK_HEIGHT ; y++) {
                        BLOCKID id = biome -> getBlocks(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, y, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                        chunk.setBlock(x, y, z, ChunkBlock(id));
                        if(id == BLOCKID::Air) {
                            if(y > 0 && chunk.getBlock(x, y - 1, z) == BLOCKID::Dirt) {
                                chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Grass));
                            }
                        }
                    }
                }
            }
        }
};