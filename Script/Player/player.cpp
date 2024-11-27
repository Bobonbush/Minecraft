#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(10.f) {
    position = glm::vec3(0.f , 250.f , 0.0f);
}

void Player::update(float deltaTime) {
    DYNAMIC_ENTITY::update(deltaTime);
    //position.x += (10.f) * deltaTime;
    
}

void Player::FixedUpdate() {
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) == GLFW_PRESS) {
        isFlying ^= 1;
    }
    DYNAMIC_ENTITY::FixedUpdate();
}