#include "Player.h"


Player * Player::instance = nullptr;
Player :: Player() {
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

Player :: ~Player() {
    // Destructor
}

void Player :: processInput(GLFWwindow *window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Player :: processMouse(GLFWwindow *window , float currentX , float currentY) {
    if (firstMouse) {
        lastMouseX = currentX;
        lastMouseY = currentY;
        firstMouse = false;
    }
    float xOffset = currentX - lastMouseX;
    float yOffset = lastMouseY - currentY;
    
    camera.ProcessMouseMovement(xOffset, yOffset);
    lastMouseX = currentX;
    lastMouseY = currentY;
}



void Player :: Update(float deltaTime, GLFWwindow *window, float currentX, float currentY) {
    processInput(window, deltaTime);
    processMouse(window, currentX , currentY);
}

void Player :: Render() {
    // Render player
}