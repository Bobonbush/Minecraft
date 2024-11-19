#include "Entity.h"
#include "Singleton.h"

class Player : public Entity, Singleton {
    private:
        void keyboardInput(float deltaTime);
        void mouseInput(float deltaTime);

        glm::vec3 m_velocity;
    
    public:
        Player();

        void update(float deltaTime);

    
};