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

        bool openingInventory = false;
        
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
        void InventoryUpdate(const float & xpos, const float & ypos);

        std::shared_ptr<Item> getCurrentItem() {
            return inventory -> getCurrentItem();
        }

        void RemoveItem(std::shared_ptr<Item> item) {
            inventory -> RemoveItem(item);
        }

        void addBlockItem(BLOCKID id, int number) {
            inventory -> addBlockItem(id, number);
        }

        void openInventory() {
            openingInventory ^= 1;
            inventory -> ShowInventoryBox();
        }

        bool isOpeningInventory() {
            return openingInventory;
        }
    

    
};

#endif // PLAYER_H