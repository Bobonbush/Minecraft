#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.h"
#include "Texture.h"


class Player {                // Another Singleton

    private:
        Camera camera;
        Player();
        static Player* instance;
        
        float lastMouseX = 0;
        float lastMouseY = 0;
        bool firstMouse = true;
        
        void processInput(GLFWwindow *window, float deltaTime) ;
        void processMouse(GLFWwindow *window, float currentX, float currentY);
    public:

        static Player* getInstance() {
            
            if (instance == nullptr) {
                instance = new Player();
            }
            return instance;
        }
        
        ~Player();


        void Update(float deltaTime, GLFWwindow *window, float currentX, float currentY);
        void Render();
        glm::mat4 getViewMatrix() {
            return camera.GetViewMatrix();
        }

        glm::mat4 getProjectionMatrix(float width, float height) {
            return camera.GetProjectionMatrix(width, height);
        }
        
};



#endif