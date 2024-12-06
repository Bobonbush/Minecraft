#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Singleton.h"
#include "Texture&Shader/ShaderManager.h"

class Player : public DYNAMIC_ENTITY, Singleton {
    private:
        static Player * m_instance;
        Player();
        const float JUMP_FORCE = 1.35f;
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

#endif // PLAYER_H