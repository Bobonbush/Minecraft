#ifndef SETTINGS_H
#define SETTINGS_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>


class Setting { // Singleton
    private :
        static Setting* instance;
        glm::vec2 resolution;
        float volume;
        int controls;

        const glm::vec3 BlockNDCSize = glm::vec3(1.0f, 1.0f , 1.0f);
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

        glm::vec3 getBlockNDCSize() {
            return BlockNDCSize;
        }


};


#endif