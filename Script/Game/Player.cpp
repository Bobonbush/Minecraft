#include "Player.h"


Player * Player::instance = nullptr;
Player :: Player() {
    camera = Camera(glm::vec3(0.0f, 15.f, 3.0f));
    Setting *settings = Setting::getInstance();

    PhysicConstant *physicConstant = PhysicConstant::getInstance();
    ShaderManager *shaderManager = ShaderManager::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    rigidbody = std::make_shared<Rigidbody>(camera.Position, glm::vec3(settings -> getBlockNDCSize().x /1.5f , settings -> getBlockNDCSize().y *2.f , settings -> getBlockNDCSize().z/1.5f ), glm::vec3(0.0f, 0.0f, 0.0f), physicConstant -> getPlayerMass() , 0.0f, 0.0f, true, ShaderManager::getInstance() -> GetShader("block"));
}

Player :: ~Player() {
    // Destructor
}

void Player :: processInput(GLFWwindow *window, float deltaTime) {
    float speed = SPEED;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(camera.Front.x * speed, 0.0f, camera.Front.z * speed) * deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(-camera.Front.x * speed, 0.0f, -camera.Front.z * speed) * deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(-camera.Right.x * speed, 0.0f, -camera.Right.z * speed) * deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        rigidbody -> AddInternalForce(glm::vec3(camera.Right.x * speed, 0.0f, camera.Right.z * speed) * deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && rigidbody -> GetUseGravity() && rigidbody -> isGround()) {
        rigidbody -> AddInternalForce(glm::vec3(0.0f, JUMPFORCE , 0.0f));
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


Frustum Player::extractFrustumPlanes() {
    glm::mat4 view = getViewMatrix();
    Setting *settings = Setting::getInstance();

    glm::mat4 projection = getProjectionMatrix(settings -> getResolution().x, settings -> getResolution().y);
    Frustum frustum;
    glm::mat4 clip = projection * view;
    
    // right plane
    frustum.rightFace.normal.x = clip[0][3] - clip[0][0];
    frustum.rightFace.normal.y = clip[1][3] - clip[1][0];
    frustum.rightFace.normal.z = clip[2][3] - clip[2][0];
    frustum.rightFace.distance = clip[3][3] - clip[3][0];
    frustum.rightFace.normalize();
    
    // left plane
    frustum.leftFace.normal.x = clip[0][3] + clip[0][0];
    frustum.leftFace.normal.y = clip[1][3] + clip[1][0];
    frustum.leftFace.normal.z = clip[2][3] + clip[2][0];
    frustum.leftFace.distance = clip[3][3] + clip[3][0];
    frustum.leftFace.normalize();
    
    // bottom plane
    frustum.bottomFace.normal.x = clip[0][3] + clip[0][1];
    frustum.bottomFace.normal.y = clip[1][3] + clip[1][1];
    frustum.bottomFace.normal.z = clip[2][3] + clip[2][1];
    frustum.bottomFace.distance = clip[3][3] + clip[3][1];
    frustum.bottomFace.normalize();
    
    // top plane
    frustum.topFace.normal.x = clip[0][3] - clip[0][1];
    frustum.topFace.normal.y = clip[1][3] - clip[1][1];
    frustum.topFace.normal.z = clip[2][3] - clip[2][1];
    frustum.topFace.distance = clip[3][3] - clip[3][1];
    
    frustum.topFace.normalize();
    
    // near plane
    frustum.nearFace.normal.x = clip[0][3] + clip[0][2];
    frustum.nearFace.normal.y = clip[1][3] + clip[1][2];
    frustum.nearFace.normal.z = clip[2][3] + clip[2][2];
    
    frustum.nearFace.distance = clip[3][3] + clip[3][2];
    frustum.nearFace.normalize();
    
    // far plane
    frustum.farFace.normal.x = clip[0][3] - clip[0][2];
    frustum.farFace.normal.y = clip[1][3] - clip[1][2];
    frustum.farFace.normal.z = clip[2][3] - clip[2][2];
    frustum.farFace.distance = clip[3][3] - clip[3][2];
    frustum.farFace.normalize();

    return frustum;
}

void Player :: Update(float deltaTime, GLFWwindow *window, float currentX, float currentY, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    processInput(window, deltaTime);
    processMouse(window, currentX , currentY);
    rigidbody -> Update(deltaTime, rigidbodies);

    camera.Position = rigidbody -> GetPosition();
    camera.Position.y += rigidbody -> GetScale().y / 4.f;
}

void Player :: Render() {
    std::vector<glm::vec3> validPositions;
    validPositions.push_back(rigidbody -> GetPosition());

    rigidbody -> ShowHitBox(getViewMatrix(), getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y), validPositions);
}