#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(10.f) {
    
}

void Player::update(float deltaTime) {
    DYNAMIC_ENTITY::update(deltaTime);
}

void Player::FixedUpdate() {
    DYNAMIC_ENTITY::FixedUpdate();
}