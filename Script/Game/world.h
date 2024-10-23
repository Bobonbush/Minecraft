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
#include "Chunks.h"


#include <thread>
class WorldRenderer {
    private:
        std::vector<std::unique_ptr<Chunk>> chunks;
        Player *player;
        std::vector<std::shared_ptr<Rigidbody>> validBodies;

        int ChunkDiameter = 1;
        

        

        static WorldRenderer * instance;

        ShaderManager * shaderManager;

        TextureManager * textureManager;

        Setting * settings;

        WorldRenderer();

        
        
    public:
        ~WorldRenderer();
        
        static WorldRenderer* getInstance() {
            if (instance == nullptr) {
                instance = new WorldRenderer();
            }
            return instance;
        }

        /* implement noise generation */


        
        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);

        void LoadChunks();

        std::vector<std::shared_ptr<Rigidbody>> & getValidBodies() {
            return validBodies;
        }
 };

#endif