#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : Entity() {
    
}

void Player::update(float deltaTime) {
    //position += velocity * deltaTime;
}

void Player::FixedUpdate() {
    
}