#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(glm::vec3(0.5f , 2.f, 0.5f)) {
    position = glm::vec3(0.f , 150.f , 0.0f);
    rotation = glm::vec3(0.f);
    velocity = glm::vec3(0.f);
    mass = 10.f;
}

void Player::update(float deltaTime) {
    DYNAMIC_ENTITY::update(deltaTime);
}

void Player::FixedUpdate() {
    DYNAMIC_ENTITY::FixedUpdate();
    if(isOnGround()) {
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            addForce(glm::vec3(0.f, JUMP_FORCE, 0.f));
        }
    }
}

