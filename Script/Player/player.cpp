#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(glm::vec3(0.5f , 1.7f, 0.5f)) {
    position = glm::vec3(0.f , 150.f , 0.0f);
    rotation = glm::vec3(0.f);
    velocity = glm::vec3(0.f);
    mass = 10.f;
    inventory = std::make_unique<InventoryManager>();
    currentItem = nullptr;
    SunBox = std::make_shared<AnimationBox>(1, "Assets/Sun.png", 16);
    
    glm::vec2 size = glm::vec2(0.055f);
    healthBar = std::make_unique<InteractiveBar>( health ,glm::vec2(-0.47f, -0.8f), size, "Assets/HealthBar/heart.png", "Assets/HealthBar/empty.png");
    meatBar = std::make_unique<InteractiveBar>(meat, glm::vec2(-0.01f, -0.8f),size * 1.25f, "Assets/HealthBar/Food.png", "Assets/HealthBar/empty_food.png");
    
    glm::vec2 pos = glm::vec2(-0.47f, -0.8f);

    pos.y += size.y * 1.05f;
    bubbleBar = std::make_unique<InteractiveBar>(bubble, pos,size, "Assets/HealthBar/bubble.png", "Assets/HealthBar/empty.png");
    spriteRenderer = SpriteRenderer::getInstance();
    textureManager = TextureManager::getInstance();

    setHeadPosition(0.35f);
}

void Player::update(float deltaTime) {

    if(isDead()) {
        return ;
    }
    DYNAMIC_ENTITY::update(deltaTime);
    inventory -> update();
    currentItem = inventory -> getCurrentItem();

    

    losingMeatCurrentTime += deltaTime;
    losingBubbleCurrentTime += deltaTime;
    if(losingMeatCurrentTime >= losingMeatMaxTime) {
        meat -= 1;
        if(meat < 0 ) {
            if(health > 1) {
                health -= 1;
            }
            meat = 0;
        }
        losingMeatCurrentTime = 0.f;
    }

    if(UnderWater) {
        if(losingBubbleCurrentTime >= losingBubbleMaxTime) {
            bubble -= 1;
            if(bubble < 0) {
                health--;
                bubble = 0;
            }
            losingBubbleCurrentTime = 0.f;
        }
        
    }else  {
        losingBubbleCurrentTime = 0.f;
        bubble = 9;
    }


    healthBar -> setHealth(health);
    meatBar -> setHealth(meat);
    bubbleBar -> setHealth(bubble);
    
}

void Player::FixedUpdate() {
    if(isDead()) {
        return ;
    }
    DYNAMIC_ENTITY::FixedUpdate();
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        Walking = true;
    } else {
        Walking = false;
    }

    if(UnderWater) {
        ApplyFriction(PhysicConst::WaterFriction);
        SoundManager * soundManager = SoundManager::GetInstance();
        soundManager -> StopSound("Step");
        soundManager -> PlaySoundEffect("WaterStep");
            
        
    }else {
        SoundManager::GetInstance() -> StopSound("WaterStep");
        if(Walking && isOnGround()) {
            
            SoundManager::GetInstance() -> PlaySoundEffect("Step");
            SoundManager::GetInstance() -> setVolume( 0.15f, "Step");
        }
        ApplyFriction();
    }

    
    if(!Walking) {
        SoundManager::GetInstance() -> StopSound("Step");
    }

    if(isOnGround()) {
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            addForce(glm::vec3(0.f, JUMP_FORCE, 0.f));
        }
    }

    
}

void Player::Render(const glm::mat4 & view, const glm::mat4 & projection) {
    
    
    
    inventory -> Render();

    if(UnderWater) {
        spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("clear"));   
        unsigned int underWaterClear = textureManager -> getTexture("Assets/UnderWater.png");
        spriteRenderer -> DrawSprite(underWaterClear, glm::vec2(0.f), glm::vec2(2.f), 0.f, glm::vec3(1.f), glm::mat4(1.0f), glm::mat4(1.0f), 0.5f);
    }

    glm::vec3 sunPosition = glm::vec3(position.x, position.y +  150.f, position.z);
    SunBox -> Render(sunPosition, glm::vec3(15.f), 0.f, 0.f, view, projection);

    ShaderManager::GetInstance() -> getShader("solid") -> setVec3("lightPosition", glm::vec3(sunPosition));
    healthBar -> Render();
    meatBar -> Render();

    if(UnderWater) {
        bubbleBar -> Render();
    }

    if(currentItem == nullptr) {
        
        return ;
    }
}

    


void Player::InventoryUpdate(const float & xpos, const float & ypos, const int & input) {
    inventory -> MouseUpdate(xpos, ypos);
    if(input == Cursor::MOUSE_EVENT::LEFT_CLICK) {
        inventory -> PickItem();
    }

    if(input == Cursor::MOUSE_EVENT::RIGHT_CLICK) {
        inventory -> PlaceOneItem();
    }
}


void Player::RemoveItem(std::shared_ptr<Item> item) {
    inventory -> RemoveItem(item);
}

void Player::addItem(int id, int number)  {
    if(id == -1) return ;
    inventory -> addItem((int) id, number);
}

std::shared_ptr<Item> Player::getCurrentItem() {
    return inventory -> getCurrentItem();
}


void Player::ReSpawn() {
    position = glm::vec3(0.f, 150.f, 0.f);
    health = 9;
    meat = 9;
    bubble = 9;
}
