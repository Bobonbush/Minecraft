#ifndef BIOME_H
#define BIOME_H
class Biomes {
    
    public:
        enum Biome {
            Desert,
            Grassland,
            Sea,
            Valley,
            Mountain, // Mean many stone
            Mountain_grass, // Mean many grass
        };
        static Biome GetBiome(float climate) {

            if(climate < 0.4) {
                return Biome::Sea;
            }

            
            if(climate < 0.55) {
                return Biome::Desert;
            }

            if(climate < 0.65) {
                return Biome::Mountain;
            }

            if(climate < 0.7) {
                return Biome::Mountain_grass;
            }

            if(climate < 0.85) {
                return Biome::Valley;
            }
            return Biome::Grassland;
            
            
        }
};

#endif // BIOME_H