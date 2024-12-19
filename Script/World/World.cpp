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

    _next = nullptr;
    deathScene = std::make_unique<DeathScene>();

    if(player -> isDead()) {
        player -> ReSpawn();
    }
}

void World::render() {
    chunkManager.renderChunks(view, projection);
    cursor -> Draw( config -> GetWidth() / 2, config -> GetHeight() / 2);
    if(player -> isDead()) {
        deathScene -> render();
        return ;
    }
    player -> Render(view , projection);
}

void World::Update(float deltaTime, const float &xpos , const float &ypos) {


    if(player -> isDead()) {
        config -> SetMouseActive(true);
        deathScene -> update(deltaTime, xpos, ypos);
        deathScene -> render();

        WaitingStage::MenuState state = deathScene -> getMenuState();

        if(state == WaitingStage::MenuState::Respawn) {
            player -> ReSpawn();
            config -> SetMouseActive(false);
        }

        if(state == WaitingStage::MenuState::QUIT) {
            backToMenu = true;
        }
        return ;
    }
    camera -> update();
    player -> update(deltaTime);
    view = camera -> GetViewMatrix();
       
    projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 160.0f); // 160

    
    Frustum * frustum = Frustum::GetInstance();
    
    frustum -> update(view, projection);
    chunkManager.update(view , projection);
    playingState -> ProcessState(*camera, chunkManager, view, projection, deltaTime);

    
}


void World::FixedUpdate(float xpos, float ypos) {
    
    if(player -> isDead()) {
        return ;
    }
    if(!config -> GetMouseActive()) {
        camera -> ProcessMouseMovement(xpos, ypos);
    }
    playingState -> FixedProcessState(*camera, chunkManager, view , projection);
    player -> FixedUpdate();
}