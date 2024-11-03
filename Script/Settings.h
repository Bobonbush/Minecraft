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

        const glm::vec3 BlockNDCSize = glm::vec3(1.f, 1.f , 1.f);
        const glm::vec3 ChunkResolution = glm::vec3(16, 64, 16);
        const glm::vec3 SubChunkResolution = glm::vec3(16, 16, 16);
        float fNear = 0.1f;
        float fFar = 300.f;

        float MaxHour = 24.f ;
        float hour = 0;
        float offsetDay = 0.25f;
        float surfaceLevel = ChunkResolution.y/3.f;


        int dayType = 0; // 0 = day, 1 = night, 2 = evening, 3 = afternoon, 4 = noon, 5 = morning
        Setting() {
            // Load settings from file
            resolution = glm::vec2(1600, 800);
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

        float getNear() {
            return fNear;
        }

        float getFar() {
            return fFar * BlockNDCSize.x;
        }

        glm::vec3 getChunkSize() {
            return ChunkResolution;
        }

        float getHour() {
            return hour / MaxHour;
        }

        float getMaxHour() {
            return MaxHour;
        }

        void Update(float deltaTime) {
            if(hour / MaxHour >= (glm::pi<float>() + offsetDay) * 2) {
                hour -= glm::pi<float>() *2 * MaxHour;
            }
            float realTime = getHour();
            if(realTime >= (glm::pi<float>() + offsetDay) / 0.5f) {
                dayType = 1;
            }else if(realTime >= (glm::pi<float>() + offsetDay) / 1.0f) {
                dayType = 2;
            } else if(realTime >= (glm::pi<float>() + offsetDay) / 1.15f) {
                dayType = 3;
            } else if(realTime >= (glm::pi<float>() + offsetDay) / 2.5f) {
                dayType = 4;
            } else {
                dayType = 5;
            }
            hour += deltaTime;
        }

        void setHour(float hour) {
            this -> hour = hour;
            
        }

        int getDayType() {
            return dayType;
        }

        void setMaxHour(float MaxHour) {
            this -> MaxHour = MaxHour;
        }

        float getOffsetDay() {
            return offsetDay;
        }

        float getSurfaceLevel() {
            return surfaceLevel;
        }

        glm::vec3 getSubChunkResolution() {
            return SubChunkResolution;
        }



};


#endif