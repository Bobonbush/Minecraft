#ifndef SETTINGS_H
#define SETTINGS_H
#include "Texture.h"
#include "Camera.h"
#include <fstream>
#include <map>


class Setting { // Singleton
    private :
        static Setting* instance;
        glm::vec2 resolution;
        float volume;
        int controls;

        const glm::vec3 BlockNDCSize = glm::vec3(2.f, 2.f , 2.f);
        const glm::vec3 ChunkResolution = glm::vec3(16, 192, 16);
        const glm::vec3 SubChunkResolution = glm::vec3(16, 16, 16);
        float fNear = 0.1f;
        float fFar = 300.f;

        float MaxHour = 24.f ;
        float hour = 0;
        float offsetDay = 0.25f;
        float surfaceLevel = ChunkResolution.y/8.f;
        int maxBlockLoad = 28672;
        int currentBlockLoad = 0;
        int currentBlockRenderer = 0;
        int maxBlockRender = 1000;

        struct Vec3Comparation {
            bool operator()(const glm::vec3& lhs, const glm::vec3& rhs) const {
                return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
            }
        };

        std::map<glm::vec3,bool, Vec3Comparation > blockMap;




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


        void saveSettings() const {
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

        const glm::vec2 getResolution() const {
            return resolution;
        }

        const int getVolume() const {
            // Get volume
        }

        const int getControls() const {
            // Get controls
        }

        const glm::vec3 getBlockNDCSize() const {
            return BlockNDCSize;
        }

        const float getNear() const {
            return fNear;
        }

        const float getFar() const {
            return fFar;
        }

        const glm::vec3 getChunkSize() const {
            return ChunkResolution;
        }

        const float getHour() const {
            return hour / MaxHour;
        }

        const float getMaxHour() const {
            return MaxHour;
        }

        void Update(float deltaTime) {

            currentBlockLoad = 0;
            maxBlockLoad = ChunkResolution.x * SubChunkResolution.y  * ChunkResolution.z;
            maxBlockLoad *= 1.25;
            maxBlockRender = ChunkResolution.x * SubChunkResolution.y * ChunkResolution.z;
            maxBlockRender /= 12;
            
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

        bool BlockLoad() {
            if(currentBlockLoad < maxBlockLoad) {
                currentBlockLoad++;
                return true;
            }
            return false;
        }

        bool BlockRender() {
            if(currentBlockRenderer < maxBlockRender) {
                currentBlockLoad++;
                return true;
            }
            return false;
        }

        void setBlockMap(glm::vec3 position, bool value) {
            blockMap[position] = value;
        }

        void deleteBlockMap(glm::vec3 position) {
            blockMap.erase(position);
        }

        const bool getBlockMap(glm::vec3 position) {
            return blockMap[position];
        }

};


#endif