#include "Player.h"

Player * Player::m_instance = nullptr;

Player::Player() : DYNAMIC_ENTITY(glm::vec3(0.5f , 1.7f, 0.5f)) {
    position = glm::vec3(0.f , 150.f , 0.0f);
    rotation = glm::vec3(0.f);
    velocity = glm::vec3(0.f);
    mass = 10.f;
    inventory = std::make_unique<InventoryManager>();
}

void Player::update(float deltaTime) {
    DYNAMIC_ENTITY::update(deltaTime);
    inventory -> update();
}

void Player::FixedUpdate() {
    DYNAMIC_ENTITY::FixedUpdate();
    if(isOnGround()) {
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            addForce(glm::vec3(0.f, JUMP_FORCE, 0.f));
        }
    }
}

void Player::Render() {
    inventory -> Render();
    if(openingInventory) {
        return ;
    }
}

