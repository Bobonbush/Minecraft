#include "World.h"


World::World() : StateBase() {
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    renderMaster = std::make_unique<RenderMaster>();
    glfwSetInputMode(Application::GetInstance() -> config -> GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    player = Player::GetInstance();

    camera -> attachedEntity = player;
}

void World::render() {
    Config * config = Application::GetInstance() -> config;
    glm::mat4 view = camera -> GetViewMatrix();
       
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 1050.0f);
        
    chunkManager.renderChunks(view, projection);
}

void World::Update(float deltaTime) {
    chunkManager.update();
    camera -> update();
    player -> update(deltaTime);
    
}


void World::FixedUpdate(float xpos, float ypos) {
    camera -> ProcessMouseMovement(xpos , ypos);
    camera -> FixedUpdate();

    

    player -> FixedUpdate();
}