#ifndef PLAYER_H
#define PLAYER_H
#include "Texture.h"
#include "Camera.h"

class Player {                // Another Singleton

    private:
        Camera camera;
        Player();
        static Player* instance;
        
        void processInput(GLFWwindow *window, float deltaTime) ;
    public:

        static Player* getInstance() {
            
            if (instance == nullptr) {
                instance = new Player();
            }
            return instance;
        }
        
        ~Player();


        void Update(float deltaTime, GLFWwindow *window);
        void Render();
        
        
};



#endif