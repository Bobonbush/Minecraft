#ifndef GAME_H
#define GAME_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>
#include "Player.h"


class Setting { // Singleton
    private :
        static Setting* instance;
        glm::vec2 resolution;
        float volume;
        int controls;
        Setting() {
            // Load settings from file
            resolution = glm::vec2(1400, 800);
        }

        void Update(float deltaTime) { 

        } 

        void Render() {

        }

    public:
        static Setting* getInstance() {
            if (instance == nullptr) {
                instance = new Setting();
            }
            return instance;
        }
        ~Setting() {
            if(instance != nullptr)
                delete instance;
        }


        void saveSettings() {
            // Save settings to file
        }

        void setResolution(int width, int height) {
            resolution = glm::vec2(width, height);
        }

        void setVolume(int volume) {
            // Set volume
        }

        void setControls(int control) {
            // Set controls
        }

        glm::vec2 getResolution() {
            return resolution;
        }

        int getVolume() {
            // Get volume
        }

        int getControls() {
            // Get controls
        }


};



class Game {
    private:
        GLFWwindow* window;
        Player *player;
        float totalTime;
        float lastTime = 0;
        void Init();

        void Update();
        void Render();

    public :
        Game();
        ~Game();

        void Run();
};





#endif