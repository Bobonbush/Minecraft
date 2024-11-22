#include "Entity.h"
#include "Singleton.h"

class Player : public Entity, Singleton {
    private:

        glm::vec3 m_velocity;
        static Player * m_instance;
        Player();
    public:
        static Player * GetInstance() {
            if(m_instance == nullptr) {
                m_instance = new Player();
            }
            return m_instance;
        }

        ~Player() {
            delete m_instance;
        }
        
        
        virtual void update(float deltaTime) override;
        virtual void FixedUpdate() override;
    

    
};