#include "Terrain.h"


NoiseGenerator::NoiseGenerator() {
                

            // Biome Noise
            noise.SetNoiseType(FastNoise::SimplexFractal);
            noise.SetFractalOctaves(10);
            noise.SetFrequency(0.006);
            //noise.SetFractalGain(0.5);
            noise.SetFractalLacunarity(1.5);
            Config * config = Config::GetInstance();
            noise.SetSeed(config -> GetSeed());

            // Mountain Noise


            // Biome Noise
            biomeNoise.SetNoiseType(FastNoise::SimplexFractal);
            biomeNoise.SetFractalOctaves(2);
            biomeNoise.SetFrequency(0.005);
            biomeNoise.SetFractalGain(0.5);
            biomeNoise.SetFractalLacunarity(1.8);
            biomeNoise.SetFractalType(FastNoise::FBM);

            biomeNoise.SetSeed(config -> GetSeed());

            caveNoise.SetNoiseType(FastNoise::SimplexFractal);
            caveNoise.SetFractalOctaves(5);
            caveNoise.SetFrequency(0.025);
            caveNoise.SetFractalGain(0.5);
            caveNoise.SetFractalLacunarity(1.8);
            caveNoise.SetFractalType(FastNoise::RigidMulti);

            caveNoise.SetSeed(config -> GetSeed());

            ClimateNoise.SetNoiseType(FastNoise::SimplexFractal);
            ClimateNoise.SetFractalOctaves(10);
            ClimateNoise.SetFrequency(0.00125);
            ClimateNoise.SetFractalGain(0.5);
            ClimateNoise.SetFractalLacunarity(0.9);
            ClimateNoise.SetFractalType(FastNoise::FBM);

            ClimateNoise.SetSeed(config -> GetSeed());


            materialNoise.SetNoiseType(FastNoise::SimplexFractal);
            materialNoise.SetFractalOctaves(5);
            materialNoise.SetFrequency(0.025);
            materialNoise.SetFractalGain(0.5);
            materialNoise.SetFractalLacunarity(3.8);
            materialNoise.SetFractalType(FastNoise::RigidMulti);

            materialNoise.SetSeed(config -> GetSeed());

            
}

float NoiseGenerator::getNoise(float x, float z) {
    return noise.GetNoise(x, z);
}

float NoiseGenerator::getNoise(float x, float y, float z) {
    return noise.GetNoise(x, y, z);
}


void NoiseGenerator::BuildChunk(ChunkSection &chunk) {
            float noiseScale = 1.f;
            for(int x = 0 ; x < Chunk::CHUNK_SIZE ; x++) {
                for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) {
                    //float noiseBiome = noise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE / noiseScale, z + chunk.getPosition().z * Chunk::CHUNK_SIZE / noiseScale) + noise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE / noiseScale /1.5f, z + chunk.getPosition().z * Chunk::CHUNK_SIZE / noiseScale / 1.5f) / 2 + noise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE / noiseScale / 2, z + chunk.getPosition().z * Chunk::CHUNK_SIZE / noiseScale / 2) / 4;
                    //noiseBiome *= biomeNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                    
                    
                    float realX = x + chunk.getPosition().x * Chunk::CHUNK_SIZE;
                    float realZ = z + chunk.getPosition().z * Chunk::CHUNK_SIZE;
                    
                    float climate = ClimateNoise.GetNoise(realX, realZ);
                    climate = (climate + 1) /2.f;
                    climate = 1.f - climate * climate;
                    Biomes::Biome biome = Biomes::GetBiome(climate);
                    
                    float noiseBiome = noise.GetNoise(realX, realZ ) +
                    (0.5 *noise.GetNoise(realX , realZ  )) *  noise.GetNoise(realX * 0.4, realZ * 0.4);
                    
                    noiseBiome = (noiseBiome + 1) / 2;
                    noiseBiome *= noiseBiome * noiseBiome;

                    float surface = 80.f;

                    float HeightScale = 100.f;
                    float probabilityofCave = 0.35f; // By default
                    if(biome == Biomes::Biome::Sea) {
                        //noiseBiome = noiseBiome * noiseBiome * noiseBiome;
                        HeightScale = 0.05f;
                        surface = 50.f;

                        waterLevel_min = 35;
                        waterLevel_max = 76;
                    }

                    if(biome == Biomes::Biome::Grassland) {
                        HeightScale = 90.f;
                        probabilityofCave = 0.25f;
                        surface = 70.f;

                        waterLevel_min = 50;
                        waterLevel_max = 76;
                    }

                    if(biome == Biomes::Biome::Mountain) {
                        HeightScale = 200.f;
                        probabilityofCave = 0.45f;
                    }

                    if(biome == Biomes::Biome::Valley) {
                        HeightScale = 95.5f;
                        probabilityofCave = 0.15f;
                        surface = 70.f;
                        waterLevel_min = 50;
                        waterLevel_max = 76;
                        
                    }

                    if(biome == Biomes::Biome::Mountain_grass) {
                        HeightScale = 150.f;
                        probabilityofCave = 0.35f;
                    }

                     int highest = noiseBiome * 3 + 1;
                    

                    noiseBiome *= HeightScale;

                    

                    
                    
                    
                    int height = noiseBiome + surface;

                    
                    
                    
                   
                    float caveprobability = caveNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                    caveprobability = (caveprobability + 1) / 2;
                    //caveprobability = (1.f - caveprobability * caveprobability);

                    probabilityofCave *= caveprobability;
                    
                    for(int y = 0 ; y < Chunk::CHUNK_SIZE ; y++) {
                        BLOCKID id = BLOCKID::Air;
                        float yPos = y + chunk.getPosition().y * Chunk::CHUNK_SIZE;
                        float caveNoises = caveNoise.GetNoise(x + chunk.getPosition().x * Chunk::CHUNK_SIZE, y + chunk.getPosition().y * Chunk::CHUNK_SIZE, z + chunk.getPosition().z * Chunk::CHUNK_SIZE);
                        
                        caveNoises = (caveNoises + 1) / 2;

                        if(y == 0 && chunk.getPosition().y == 0) {
                            id = BLOCKID::Bedrock;
                            chunk.setBlock(x, y, z, ChunkBlock(id));
                            continue;
                        }

                        if(yPos > height && yPos <= waterLevel_max && yPos >= waterLevel_min) {
                            chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Water));
                            continue;
                        }

                        if(yPos > height && biome != Biomes::Biome::Sea) {
                            break;
                        }

                        

                        if(biome == Biomes::Biome::Sea) {
                            if(yPos > waterLevel_max) {
                                chunk.setBlock(x, y, z, ChunkBlock(id));
                                continue;
                            }
                        }

                        

                        

                        if( (caveNoises * caveNoises < probabilityofCave )) {
                            //std::cout << yPos << " " << height << '\n';
                            if(biome == Biomes::Biome::Sea) {
                                if(yPos <= height && yPos <= waterLevel_max-1 && yPos >= waterLevel_min) {
                                    chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Water));
                                }else {
                                    chunk.setBlock(x, y, z, ChunkBlock(BLOCKID::Water));
                                }
                            }else {
                                chunk.setBlock(x, y, z, ChunkBlock(id));
                            }
                            continue;
                        }
                        

                        bool isOred = false;
                        for(int i = 3 ; i >= 0 ; i--) {

                            float low = oreMinLevel[i] * height;
                            float high = oreMaxLevel[i] * height;
                            if(yPos >= low && yPos <= high) {
                                if(isOre(x + chunk.getPosition().x * Chunk::CHUNK_SIZE + i, y + chunk.getPosition().y * Chunk::CHUNK_SIZE + i, z + chunk.getPosition().z * Chunk::CHUNK_SIZE + i,low, high, i)) {
                                    id = static_cast<BLOCKID>(i + 11);
                                    chunk.setBlock(x, y, z, ChunkBlock(id));
                                    isOred = true;
                                    break;
                                }
                            }
                        }
                        

                        if(isOred) continue;

                        

                        if(biome == Biomes::Biome::Desert) {
                            if(yPos <= height && yPos >= height - highest) {
                                id = BLOCKID::Sand;
                            }else {
                                id = BLOCKID::Stone;
                            }
                        } else if(biome == Biomes::Biome::Grassland || biome == Biomes::Biome::Valley || biome == Biomes::Biome::Mountain_grass) {
                            if(yPos == height ) {
                                id = BLOCKID::Grass;
                            }else {
                                if(yPos <= height && yPos >= height - highest) {
                                    id = BLOCKID::Dirt;
                                }else {
                                    id = BLOCKID::Stone;
                                }
                            }
                        }else if(biome == Biomes::Biome::Mountain) {
                            id = BLOCKID::Stone;
                        }else if(biome == Biomes::Biome::Sea) {

                            //std::cout << yPos << " " << height << '\n';
                            if(yPos <= height && yPos <= waterLevel_max && yPos >= waterLevel_min) {
                                id = BLOCKID::Stone;
                            }else if(yPos <= waterLevel_max && yPos >= waterLevel_min) {
                                id = BLOCKID::Water;
                            }else {
                                id = BLOCKID::Stone;
                            }
                        }


                        
                        
                        chunk.setBlock(x, y, z, ChunkBlock(id));
                    }
                }
            }
        }