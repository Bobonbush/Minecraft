#include "optionMenu.h"


OptionMenu::OptionMenu() {
    unsigned Pickage = TextureManager::getInstance() -> getTexture("Assets/Title.png");
    Pickaxe = std::make_unique<AppearSprite>(Pickage, glm::vec2(0,0), glm::vec2(3.75f, 0.35f));
    
    TitleName = std::make_unique<AppearText>("ELDEN CRAFT", "Assets/Font/Mantinia.otf", glm::vec2(0, 0.025), glm::vec2(0.0f, 0.0f), 150.f, 2.0f, glm::vec3(238.0/255.0, 220.0/255.0, 182.0 /255.0));
    TitleName -> setAppearant(1.0f);
    Pickaxe = std::make_unique<AppearSprite>(Pickage, glm::vec2(0, 0), glm::vec2(3.75, 0.35));
    Pickaxe -> setAppearant(1.0f);
    glm::vec2 buttonSize = glm::vec2(6.0f, 3.05f);
    std::pair<float ,float > realSize = TextureManager::getInstance() -> getTextureSize("Assets/bounds.png");
    Config * config = Config::GetInstance();
    realSize.first = realSize.first / config -> GetWidth();
    realSize.second = realSize.second / config -> GetHeight();
    buttonSize.x *= realSize.first;
    buttonSize.y *= realSize.second;

    buttons.push_back(std::make_unique<Button>(TextureManager::getInstance() -> getTexture("Assets/bounds.png"), glm::vec2(0, -0.5), buttonSize, "NEW GAME", "Assets/Font/Mantinia.otf", 18.f, 2.2f, glm::vec3(238.0/255.0, 220.0/255.0, 182.0 /255.0)));
    buttons.push_back(std::make_unique<Button>(TextureManager::getInstance() -> getTexture("Assets/bounds.png"), glm::vec2(0, -0.75), buttonSize, "QUIT", "Assets/Font/Mantinia.otf", 18.f, 2.2f, glm::vec3(238.0/255.0, 220.0/255.0, 182.0 /255.0)));
} 

OptionMenu::~OptionMenu() {

}

void OptionMenu::render() {
    TitleName -> render();
    Pickaxe -> render();
    for(auto & button : buttons) {
        button -> render();
    }
}

void OptionMenu::update(float deltaTime, const float &xpos, const float &ypos) {
    TitleName -> update(deltaTime);
    Pickaxe -> update(deltaTime);

    for(auto & button : buttons) {
        button -> update(deltaTime, xpos, ypos);
    }

    if(cooldown > 0) {
        cooldown -= deltaTime;
        return ;
    }

    if(buttons[0] -> isClickedButton()) {
        menuState = MenuState::PLAY;
    }
    if(buttons[1] -> isClickedButton()) {
        menuState = MenuState::QUIT;
        glfwSetWindowShouldClose(Config::GetInstance() -> GetWindow(), true);
    }
}

void OptionMenu::FixedUpdate() {
}

void OptionMenu::ProcessState() {
}