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
#include <memory>
#include "World.h"

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

            //std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Roughly 60 FPS

    public :
        Game();
        ~Game();

        void Run();
};





#endif