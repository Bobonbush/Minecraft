#include "Player.h"


Player * Player::instance = nullptr;
Player :: Player() {
    camera = Camera(glm::vec3(100.0f, 193.f, -100.0f));
    Setting *settings = Setting::getInstance();

    PhysicConstant *physicConstant = PhysicConstant::getInstance();
    ShaderManager *shaderManager = ShaderManager::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    rigidbody = std::make_shared<Rigidbody>(camera.Position, glm::vec3(settings -> getBlockNDCSize().x /1.5f , settings -> getBlockNDCSize().y *2.f , settings -> getBlockNDCSize().z/1.5f ), glm::vec3(0.0f, 0.0f, 0.0f), physicConstant -> getPlayerMass() , 0.0f, 0.0f, false, ShaderManager::getInstance() -> GetShader("block"));
}

Player :: ~Player() {
    // Destructor
}

void Player :: processInput(GLFWwindow *window) {
    float speed = SPEED;

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        speed *= 3.5f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE  && ButtonPressed == true) {
        //speed *= 2.5f;
        rigidbody -> SetUseGravity(!rigidbody -> GetUseGravity());
    }
    ButtonPressed = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(camera.Front.x * speed, 0.0f, camera.Front.z * speed));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(-camera.Front.x * speed, 0.0f, -camera.Front.z * speed) );
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(-camera.Right.x * speed, 0.0f, -camera.Right.z * speed) );
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(camera.Right.x * speed, 0.0f, camera.Right.z * speed));
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && rigidbody -> GetUseGravity() && rigidbody -> isGround()) {
        rigidbody -> AddInternalForce(glm::vec3(0.0f, JUMPFORCE , 0.0f));
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && !rigidbody -> GetUseGravity()) {
        rigidbody -> AddInternalForce(glm::vec3(0.0f, -speed , 0.0f));
        //rigidbody -> SetPosition(rigidbody -> GetPosition() + glm::vec3(0.0f, -speed , 0.0f));
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS && !rigidbody -> GetUseGravity()) {
        rigidbody -> AddInternalForce(glm::vec3(0.0f, speed * 5.f , 0.0f));
        //rigidbody -> SetPosition(rigidbody -> GetPosition() + glm::vec3(0.0f, speed , 0.0f));
    
    }
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

void Player :: Update(float deltaTime, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    
    rigidbody -> Update(deltaTime, rigidbodies);

    camera.Position = rigidbody -> GetPosition();
    camera.Position.y += rigidbody -> GetScale().y / 4.f;
    ShaderManager *shaderManager = ShaderManager::getInstance();
    shaderManager -> GetShader("block") -> use();
    shaderManager -> GetShader("block") -> setVec3("viewPos", camera.Position);
}

void Player::FixedUpdate(GLFWwindow *window, float currentX, float currentY, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies, float Alpha) {
    
    rigidbody -> FixedUpdate(Alpha, rigidbodies);
    processInput(window);
    processMouse(window, currentX , currentY);

    
      
}

void Player :: Render() {
    std::vector<glm::vec3> validPositions;
    validPositions.push_back(rigidbody -> GetPosition());
    
    //rigidbody -> ShowHitBox(getViewMatrix(), getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y), validPositions);
}