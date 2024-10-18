#include "game.h"




// WorldRenderer Define

WorldRenderer *WorldRenderer :: instance = nullptr;

WorldRenderer :: WorldRenderer() {
    shaderManager = ShaderManager::getInstance();
    textureManager = TextureManager::getInstance();
    settings = Setting::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    for(int i = 0 ; i < 400; i++) {
        for(int j = 0 ; j < 400 ; j++) blocks.push_back(std::make_unique<Dirt>(glm::vec3(i * settings -> getBlockNDCSize().x, 0, j * settings -> getBlockNDCSize().z), settings -> getBlockNDCSize(), glm::vec3(0, 0, 0), shaderManager -> GetShader("block")));
    }
}

WorldRenderer :: ~WorldRenderer() {
    delete instance;
}

void WorldRenderer :: Render(glm::mat4 view, glm::mat4 projection) {
    for (auto &block : blocks) {
        block -> Render(view, projection);
    }
}

void WorldRenderer :: Update(float deltaTime) {
    for (auto &block : blocks) {
        block -> Update(deltaTime);
    }
}




//Game Define

Game :: Game() {
    window = nullptr;
}

Game :: ~Game() {
    glfwDestroyWindow(window);
    delete block;
    delete block2;
}

void Game::Update() {
    totalTime = glfwGetTime();
    float deltaTime = totalTime - lastTime;
    world -> Update(deltaTime);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastTime = totalTime;


    player -> Update(deltaTime, window, xpos, ypos);
}

void Game::Render() {
    glm::mat4 view = player -> getViewMatrix();
    glm::mat4 projection = player -> getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y);
    player -> Render();
    world -> Render(view, projection);
}

void Game::Init() {
    if (!glfwInit()) {
        std::cout << "Error: GLFW not initialized" << std::endl;
        return;
    }

            
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Setting *settings = Setting::getInstance();

    window = glfwCreateWindow(settings -> getResolution().x , settings -> getResolution().y, "Elden Craft", NULL, NULL);
    if (!window) {
        std::cout << "Error: Window not created" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: GLAD not initialized" << std::endl;
        glfwTerminate();
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);
    
    glViewport(0, 0, settings -> getResolution().x , settings -> getResolution().y);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
}

void Game::Run() {
    Init();
    player = Player::getInstance();
    world = WorldRenderer::getInstance();
    



    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Update();
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

     glfwTerminate();

}