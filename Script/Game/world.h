#ifndef WORLD_H
#define WORLD_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>
#include "Player.h"
#include "Blocks.h"
#include "Settings.h"
#include "Resource/ShaderLoad.h"
#include "Resource/TextureLoad.h"
#include <memory>
#include "Algorithm.h"
#define DB_PERLIN_IMPL
#include "Resource/db_perlin.hpp"
class WorldRenderer {
    private:
        std::vector<std::unique_ptr<Block>> blocks;

        enum BlockType {
            WATER,
            SAND,
            DIRT,
            STONE
        };

        

        static WorldRenderer * instance;

        ShaderManager * shaderManager;

        TextureManager * textureManager;

        Setting * settings;

        WorldRenderer();

        void SoftNoise(std::vector<std::vector<float>> &elavationMap) {
            int n = (int)elavationMap.size();
            for (int i = 0; i < n; i++) {
                int m = (int)elavationMap[i].size();
                for (int j = 0; j < m; j++) {
                    if(i + 1 < n )
                        elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i+1][j] );
                    if(j + 1 < m)
                        elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i][j+1] );
                    if(i + 1 < n && j + 1 < m)
                        elavationMap[i][j] = SPA::min(elavationMap[i][j] , elavationMap[i+1][j+1] );
                }
            }
        }
        
    public:
        ~WorldRenderer();
        
        static WorldRenderer* getInstance() {
            if (instance == nullptr) {
                instance = new WorldRenderer();
            }
            return instance;
        }

        /* implement noise generation */

        void CreateWorld();


        
        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};

#endif