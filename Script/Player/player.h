#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Singleton.h"
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureManager.h"
#include "Inventory/InventoryManager.h"
#include "States/Cursor.h"
#include "Renderer/AnimationBoxRenderer.h"
#include "InteractiveBar.h"
#include "Renderer/SpriteRenderer.h"
#include "Texture&Shader/SoundManager.h"

class Player : public DYNAMIC_ENTITY, Singleton {
    private:
        static Player * m_instance;
        const float JUMP_FORCE = 1.35f;
        std::unique_ptr<InventoryManager> inventory;
        std::shared_ptr<Item> currentItem;

        std::shared_ptr<AnimationBox> SunBox;

        bool headUnderWater = false;
        bool FirstTimeSpawn = true;
        Player();

        bool openingInventory = false;

        float losingMeatMaxTime = 100.5f;
        float losingMeatCurrentTime = 0.f;
        float heartRate = 1.5f;
        float heartCurrentTime = 0.f;

        float losingBubbleMaxTime = 1.5f;
        float losingBubbleCurrentTime = 0.f;

        int maxAmor = 9;
        int currentAmor = 9;

        float exhaustConst = 0.5f;

        SpriteRenderer * spriteRenderer;
        TextureManager * textureManager;
        
    public:
        static Player * GetInstance() {
            if(m_instance == nullptr) {
                m_instance = new Player();
            }
            return m_instance;
        }

        int health = 9;
        int meat = 9;
        int bubble = 9;

        std::unique_ptr<InteractiveBar> healthBar;
        std::unique_ptr<InteractiveBar> meatBar;
        std::unique_ptr<InteractiveBar> bubbleBar;
        std::unique_ptr<InteractiveBar> AmorBar;

        ~Player() {
            delete m_instance;
        }
        
        
        void update(float deltaTime) ;
        void FixedUpdate() ;
        void Render(const glm::mat4 & view, const glm::mat4 & projection) ;
        void InventoryUpdate(const float & xpos, const float & ypos, const int & input);

        std::shared_ptr<Item> getCurrentItem();
        
        /*
        std::shared_ptr<Item> getCursorItem() {
            return inventory -> getCurrentItem();
        }
        */

        void RemoveItem(std::shared_ptr<Item> item);

        void addItem(int id, int number);

        void openInventory() {
            openingInventory ^= 1;
            if(!openingInventory) {
                UsingNormalInventory();
            }
            inventory -> ShowInventoryBox();
        }

        void CloseInventory() {
            openingInventory = false;
            UsingNormalInventory();
            inventory -> CloseInventory();
        }

        bool isOpeningInventory() {
            return openingInventory;
        }

        void UsingCraftingTable() {
            inventory -> UsingCraftingTable();
        }

        void UsingNormalInventory() {
            inventory -> UsingNormalInventory();
        }

        const bool isDead() const {
            return health <= 0;
        }

        void ReSpawn();

        void setHeadUnderWater(bool headUnderWater) {
            this -> headUnderWater = headUnderWater;
        }


        void Eat(int value) {
            meat += value;
            SPA::clamp(meat, 0, 9);
        }



        
    

    
};

#endif // PLAYER_H