#include "mainScreen.h"

MainScreen::MainScreen() {
    spriteRenderer = SpriteRenderer::getInstance();

    glm::vec3 EldenRingFontColor = glm::vec3(238.0/255.0, 220.0/255.0, 182.0 /255.0);
    
    TitleName = std::make_unique<AppearText>("ELDEN CRAFT", "Assets/Font/Mantinia.otf", glm::vec2(0, 0.025), glm::vec2(0.0f, 0.0f), 150.f, 2.0f, EldenRingFontColor);
    StartGame = std::make_unique<ReAppearingText>("PRESS ANY BUTTON", "Assets/Font/Mantinia.otf", glm::vec2(0, -0.5), glm::vec2(0.1f, 0.1f), 18.f, 2.2f, glm::vec3(1.0f));
    StudioName = std::make_unique<ReAppearingTextOnlyOnce>("THUNDER HOUND", "Assets/Font/Mantinia.otf", glm::vec2(0.0f, -0.75), glm::vec2(0.5f, 0.5f), 54.f, 2.f, glm::vec3(1.0f, 1.0f, 1.0f));
    LoadedStudioName = false;
    StudioName -> setAlphaSpeed(0.25f);
    ShaderManager::GetInstance() -> addShader("Screen", "Shader/Screen.vs", "Shader/Screen.fs");
    

    Pickage = TextureManager::getInstance() -> getTexture("Assets/Title.png");
    Pickaxe = std::make_unique<AppearSprite>(Pickage, Titleposition, TitleSize);
    float aspect = 1.f/ Config::GetInstance() -> GetAspectRatio();
    TitleSize.x *= aspect;

    StudioLogo = std::make_unique<ReAppearingSpriteOnlyOnce>(TextureManager::getInstance() -> getTexture("Assets/Thunder Hound.png"), glm::vec2(0.0f, 0.0f), glm::vec2(1.f, 1.f));
    ClearScreen = std::make_unique<ReAppearingSpriteOnlyOnce>(TextureManager::getInstance() -> getTexture("Assets/Clear.png"), glm::vec2(0.0f, 0.0f), glm::vec2(4.5f, 2.f));
    StudioLogo -> setAlphaSpeed(0.25f);
    ClearScreen -> setAlphaSpeed(0.25f);
    
    setNextState(std::make_unique<OptionMenu>());

    soundManager = SoundManager::GetInstance();

    soundManager -> PlaySound("Menu", true);
}

MainScreen::~MainScreen() {
    //delete spriteRenderer;
}

void MainScreen::render() {
    
    if(!LoadedStudioName) {
        StudioName -> render();
        StudioLogo -> render();
        ClearScreen -> render();
        if(StudioName -> isFinished()) {
            LoadedStudioName = true;
            
        }
        return ;
    }

    if(afterIntroCurrentTime < afterIntroMaxTime) {
        return ;
    }

    TitleName -> render();
    Pickaxe -> render();

    if(TitleName -> isFinished()) {
        StartGame -> render();
    }
    
}

void MainScreen::update(float deltaTime, const float &xpos, const float &ypos) {
    
    if(!LoadedStudioName) {
        StudioName -> update(deltaTime);
        StudioLogo -> update(deltaTime);
        ClearScreen -> update(deltaTime);
        if(StudioName -> isFinished()) {
            LoadedStudioName = true;
        }
        return ;
    }

    if(afterIntroCurrentTime < afterIntroMaxTime) {
        afterIntroCurrentTime += deltaTime;
        return ;
    }
    TitleName -> update(deltaTime);
    Pickaxe -> update(deltaTime);
    if(TitleName -> isFinished()) {
        StartGame -> update(deltaTime);
        if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            _next = true;
        }
    }
    
}

void MainScreen::FixedUpdate() {
    //spriteRenderer -> FixedUpdate();
}

void MainScreen::ProcessState() {
    //spriteRenderer -> ProcessState();
}




