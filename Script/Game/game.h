#ifndef GAME_H
#define GAME_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>
#include "Player.h"
#include "Blocks.h"
#include "Settings.h"
#include "Resource/ShaderLoad.h"
#include "Resource/TextureLoad.h"

class WorldRenderer {
    private:
        std::vector<Block*> blocks;

        

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

        void CreateWorld() {
        }


        
        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
        void AddBlock(Block *block);
        void RemoveBlock(Block *block);
        void Clear();
};


class Game {
    private:
        GLFWwindow* window;
        Player *player;
        float totalTime;
        float lastTime = 0;
        Block *block;
        Block * block2;
        WorldRenderer * world;


        void Init();

        void Update();
        void Render();

    public :
        Game();
        ~Game();

        void Run();
};





#endif