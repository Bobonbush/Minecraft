#include "PlayingState.h"

PlayingState::PlayingState() : StateBase() {

}

void PlayingState::render(std::unique_ptr<RenderMaster>& rendererMaster) {
    rendererMaster -> drawQuads(glm::vec3(0.0f, 0.0f, 0.0f));
}

void PlayingState::Update(float deltaTime) {
    
}