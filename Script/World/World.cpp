#include "World.h"


World::World() : StateBase() {
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    renderMaster = std::make_unique<RenderMaster>();
    glfwSetInputMode(Application::GetInstance() -> config -> GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    player = Player::GetInstance();

    camera -> attachedEntity = player;
}

void World::render() {
    chunkManager.renderChunks(view, projection);
}

void World::Update(float deltaTime) {
    camera -> update();
    player -> update(deltaTime);
    
    Config * config = Application::GetInstance() -> config;
    view = camera -> GetViewMatrix();
       
    projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 1000.0f);
    Frustum * frustum = Frustum::GetInstance();
    frustum -> update(view, projection);
    chunkManager.update(view , projection);
}


void World::FixedUpdate(float xpos, float ypos) {
    camera -> ProcessMouseMovement(xpos , ypos);
    camera -> FixedUpdate();

    

    player -> FixedUpdate();
}