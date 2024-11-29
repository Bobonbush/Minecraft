#include "World.h"


World::World() : StateBase() {
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    renderMaster = std::make_unique<RenderMaster>();
    glfwSetInputMode(Application::GetInstance() -> config -> GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    player = Player::GetInstance();
    cursor = Cursor::GetInstance();

    camera -> attachEntity(player);
    config = Application::GetInstance() -> config;
    playingState = PlayingState::GetInstance();
}

void World::render() {
    chunkManager.renderChunks(view, projection);
    cursor -> Draw( config -> GetWidth() / 2, config -> GetHeight() / 2);
}

void World::Update(float deltaTime) {
    camera -> update();
    player -> update(deltaTime);
    
    
    view = camera -> GetViewMatrix();
       
    projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 160.0f);

    
    Frustum * frustum = Frustum::GetInstance();
    
    frustum -> update(view, projection);
    chunkManager.update(view , projection);
    playingState -> ProcessState(*camera, chunkManager, view, projection);


}


void World::FixedUpdate(float xpos, float ypos) {
    playingState -> FixedProcessState(*camera, chunkManager, view , projection);
    camera -> ProcessMouseMovement(xpos, ypos);

    player -> FixedUpdate();
}