#include "SceneState.h"


void SceneState::render() {
    if(changeBetweenState < changeBetweenStateMax) {
        return ;
    }
    states.top() -> render();
}

void SceneState::Update(float deltaTime, const float &xpos, const float &ypos) {
    if(changeBetweenState < changeBetweenStateMax) {
        changeBetweenState += deltaTime;
        return ;
    }
    states.top() -> Update(deltaTime, xpos, ypos);

    std::unique_ptr<StateBase> nextState = states.top() -> isNext();
    if(nextState != nullptr) {;
        //states.pop();

        pushState(std::move(nextState));
    }

    if(states.top() -> isFinished()) {
        popState();
        std::cout << "YES" << '\n';
    }
}

void SceneState::FixedUpdate(float xpos, float ypos) {
    if(changeBetweenState < changeBetweenStateMax) {
        //changeBetweenState += 0.01f;
        return ;
    }
    states.top() -> FixedUpdate(xpos, ypos);
}

void SceneState::pushState(std::unique_ptr<StateBase> state) {
    changeBetweenState = 0.0f;
    states.push(std::move(state));
}

void SceneState::popState() {
    
    changeBetweenState = 0.0f;
    states.pop();
}