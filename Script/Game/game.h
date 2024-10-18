#ifndef GAME_H
#define GAME_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>
#include "Player.h"
#include "Blocks.h"
#include "Settings.h"





class Game {
    private:
        GLFWwindow* window;
        Player *player;
        float totalTime;
        float lastTime = 0;
        Block *block;
        void Init();

        void Update();
        void Render();

    public :
        Game();
        ~Game();

        void Run();
};





#endif