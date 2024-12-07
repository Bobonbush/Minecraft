#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Singleton.h"
#include "Texture&Shader/ShaderManager.h"
#include "InventoryManager.h"

class Player : public DYNAMIC_ENTITY, Singleton {
    private:
        static Player * m_instance;
        const float JUMP_FORCE = 1.35f;
        std::unique_ptr<InventoryManager> inventory;
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
        void Render() ;

        std::shared_ptr<Item> getCurrentItem() {
            return inventory -> getCurrentItem();
        }
    

    
};

#endif // PLAYER_H