#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.h"
#include "Texture.h"
#include "Settings.h"
#include "Physic/rigidbody.h"


class Player {                // Another Singleton

    private:

        
        const float SPEED = 4.5f;
        const float JUMPFORCE = 80.f;
        Camera camera;
        Player();
        static Player* instance;
        
        float lastMouseX = 0;
        float lastMouseY = 0;
        bool firstMouse = true;
        std::shared_ptr<Rigidbody> rigidbody;
        void processInput(GLFWwindow *window, float deltaTime) ;
        void processMouse(GLFWwindow *window, float currentX, float currentY);

        void CopyCameraCharecteristics() {
            rigidbody -> SetPosition(camera.Position);
        }
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
            Setting *settings = Setting::getInstance();
            return camera.GetProjectionMatrix(width, height,  settings -> getNear(), settings -> getFar());
        }


        Frustum extractFrustumPlanes() ;


        // Getters


        glm::vec3 GetPosition() {
            return rigidbody -> GetPosition();
        }

        glm::vec3 GetScale() {
            return rigidbody -> GetScale();
        }

        glm::vec3 GetRotation() {
            return rigidbody -> GetRotation();
        }

        // Setters

        void SetPosition(glm::vec3 position) {
            rigidbody -> SetPosition(position);
        }

        void SetScale(glm::vec3 scale) {
            rigidbody -> SetScale(scale);
        }

        void SetRotation(glm::vec3 rotation) {
            rigidbody -> SetRotation(rotation);
        }
        
};



#endif