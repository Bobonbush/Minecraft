#include "World.h"


World::World() : StateBase() {
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    renderMaster = std::make_unique<RenderMaster>();
    glfwSetInputMode(Application::GetInstance() -> config -> GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void World::render() {
    Config * config = Application::GetInstance() -> config;
    glm::mat4 view = camera -> GetViewMatrix();
       
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 100.0f);
        
    for(auto & chunk : chunks) {
        renderMaster -> drawChunk(chunk.mesh);
    }
    renderMaster -> finishRender(view, projection);
}

void World::Update(float deltaTime) {
    
}


void World::FixedUpdate(float xpos, float ypos) {
    camera -> ProcessMouseMovement(xpos , ypos);

    float elapsedTime = 1.f;

    Config * config = Application::GetInstance() -> config;

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::FORWARD, elapsedTime);
    }
    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::BACKWARD, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::LEFT, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::RIGHT, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::UP, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera -> ProcessKeyboard(Camera_Movement::DOWN, elapsedTime);
    }
}