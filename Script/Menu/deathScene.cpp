#include "deathScene.h"


DeathScene::DeathScene() {
    TitleName =  std::make_unique<AppearText>("YOU DIED", "Assets/Font/Mantinia.otf", glm::vec2(0, 0.025), glm::vec2(0.0f, 0.3f), 120.f, 2.0f, glm::vec3(255.0/255.0, 0.0/255.0, 0.0 /255.0));
    TitleName -> setAlphaSpeed(0.15f);
    TitleName -> setAppearant(0.00001f);
    ClearScreen = std::make_unique<AppearSprite>(TextureManager::getInstance() -> getTexture("Assets/DeathClear.png"), glm::vec2(0.0f, 0.0f), glm::vec2(4.5f, 2.f));
    ClearScreen -> setAlphaSpeed(0.15f);
    //ShaderManager::GetInstance() -> addShader("Screen", "Shader/Screen.vs", "Shader/Screen.fs");
    SoundManager::GetInstance() -> PlaySound("Death");

    glm::vec2 buttonSize = glm::vec2(8.0f, 4.05f);

    std::pair<float ,float > realSize = TextureManager::getInstance() -> getTextureSize("Assets/bounds.png");
    Config * config = Config::GetInstance();
    realSize.first = realSize.first / config -> GetWidth();
    realSize.second = realSize.second / config -> GetHeight();
    buttonSize.x *= realSize.first;
    buttonSize.y *= realSize.second;

    buttons.push_back(std::make_unique<Button>(TextureManager::getInstance() -> getTexture("Assets/bounds.png"), glm::vec2(0, -0.5), buttonSize, "AGAIN ?", "Assets/Font/Mantinia.otf", 30.f, 2.2f, glm::vec3(255.0/255.0, 255.0/255.0, 255.0 /255.0)));
    buttons.push_back(std::make_unique<Button>(TextureManager::getInstance() -> getTexture("Assets/bounds.png"), glm::vec2(0, -0.75), buttonSize, "QUIT", "Assets/Font/Mantinia.otf", 30.f, 2.2f, glm::vec3(255.0/255.0, 255.0/255.0, 255.0 /255.0)));
}

DeathScene::~DeathScene() {
    
}

void DeathScene::render() {
    TitleName -> render();
    

    if(TitleName -> isFinished()) {
        for(auto & button : buttons) {
            button -> render();
        }
    }
    ClearScreen -> render();
    
}

void DeathScene::update(float deltaTime, const float &xpos , const float &ypos) {
    ClearScreen -> update(deltaTime);
    TitleName -> update(deltaTime);
    if(isPlaySong == false) {
        SoundManager::GetInstance() -> PlaySound("Death");
        isPlaySong = true;
    }

    if(TitleName -> isFinished()) {
        for(auto & button : buttons) {
            button -> update(deltaTime, xpos, ypos);
        }
    }

    if(buttons[0] -> isClickedButton()) {
        menuState = MenuState::Respawn;
        Reset();
    }

    if(buttons[1] -> isClickedButton()) {
        menuState = MenuState::QUIT;
        Reset();
    }
}

void DeathScene::Reset() {
    TitleName -> setAppearant(0.00001f);
    TitleName -> setAlphaSpeed(0.15f);
    ClearScreen -> setAppearant(0.00001f);
    ClearScreen -> setAlphaSpeed(0.15f);
    isPlaySong = false;
}

void DeathScene::FixedUpdate() {
    
}

void DeathScene::ProcessState() {
    
}