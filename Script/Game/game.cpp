#include "game.h"




// WorldRenderer Define

WorldRenderer *WorldRenderer :: instance = nullptr;

WorldRenderer :: WorldRenderer() {
    shaderManager = ShaderManager::getInstance();
    textureManager = TextureManager::getInstance();
    shaderManager -> LoadShader("block", "Shaders/block.vs", "Shaders/block.fs");
    blocks.push_back(new Dirt(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), shaderManager -> GetShader("block")));
    blocks.push_back(new Stone(glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), shaderManager -> GetShader("block")));
    blocks.push_back(new Water(glm::vec3(2, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), shaderManager -> GetShader("block")));
    
}

WorldRenderer :: ~WorldRenderer() {
    for (Block *block : blocks) {
        delete block;
    }
    delete instance;
}

void WorldRenderer :: Render(glm::mat4 view, glm::mat4 projection) {
    for (Block *block : blocks) {
        block -> Render(view, projection);
    }
}

void WorldRenderer :: Update(float deltaTime) {
    for (Block *block : blocks) {
        block -> Update(deltaTime);
    }
}

void WorldRenderer :: AddBlock(Block *block) {
    blocks.push_back(block);
}

void WorldRenderer :: RemoveBlock(Block *block) {
    blocks.erase(std::remove(blocks.begin(), blocks.end(), block), blocks.end());
}

void WorldRenderer :: Clear() {
    blocks.clear();
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