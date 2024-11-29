#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(10.f) {
    position = glm::vec3(0.f , 150.f , 0.0f);
}

void Player::update(float deltaTime) {
    DYNAMIC_ENTITY::update(deltaTime);
    //position.x += (10.f) * deltaTime;
    
}

void Player::FixedUpdate() {
    DYNAMIC_ENTITY::FixedUpdate();
}