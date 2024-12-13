#include "Texture.h"


class Timer { // Timer for breaking blocks
    private:
        float maxTime = 0.5f;
        float currentTime = 0.f;
        float efficiency = 0.f;    

        int inUse = -1;   // -1 means hand


        glm::vec3 blockPosition = glm::vec3(-191931, 0 ,0);
    public :
        Timer() = default;
        Timer(float maxTime);
        Timer(float maxTime, float efficiency);

        void Update(float deltaTime);
        void Reset();

        bool isFinished() ;

        const int getInUse() const;

        const glm::vec3 & getBlockPosition();
        void setBlockPosition(const glm::vec3 & position);

        void setInUse(int id);

        const float getCurrentTime() const;
        const float getMaxTime() const;

};