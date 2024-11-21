#include "SceneState.h"


void SceneState::render() {
    states.top() -> render();
}

void SceneState::Update(float deltaTime) {
    states.top() -> Update(deltaTime);
}

void SceneState::FixedUpdate(float xpos, float ypos) {
    states.top() -> FixedUpdate(xpos, ypos);
}

void SceneState::pushState(std::unique_ptr<StateBase> state) {
    states.push(std::move(state));
}

void SceneState::popState() {
    states.pop();
}