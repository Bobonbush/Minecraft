#include "menu.h"

Menu::Menu() {
    Screen = std::make_unique<MainScreen>();   // First Time appearance
    _next = nullptr;
}

void Menu::render() {
    Screen -> render();
}

void Menu::Update(float deltaTime, const float &xpos, const float &ypos) {
    Screen -> update(deltaTime, xpos , ypos);
    if(Screen -> isNext()) {
        Screen = Screen -> getNextState();
    }
    if(Screen -> getMenuState() == WaitingStage::MenuState::PLAY) {
        _next = std::make_unique<World>();
        SoundManager::GetInstance() -> StopAllSounds();
    }
}

void Menu::FixedUpdate(float xpos, float ypos) {
    Screen -> FixedUpdate();
}