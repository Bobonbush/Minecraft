#include "Entity.h"
#include "Singleton.h"

class Player : public DYNAMIC_ENTITY, Singleton {
    private:
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
        
        
        void update(float deltaTime) ;
        void FixedUpdate() ;
    

    
};