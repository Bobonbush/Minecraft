#include "game.h"



//Game Define

Game :: Game() {
    window = nullptr;
}

Game :: ~Game() {
    glfwDestroyWindow(window);
    delete block;
}

void Game::Update() {
    totalTime = glfwGetTime();
    float deltaTime = totalTime - lastTime;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastTime = totalTime;
    block -> Update(deltaTime);


    player -> Update(deltaTime, window, xpos, ypos);

}

void Game::Render() {
    glm::mat4 view = player -> getViewMatrix();
    glm::mat4 projection = player -> getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y);
    player -> Render();
    block -> Render(view, projection);
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
    Shader shader("Shaders/block.vs", "Shaders/block.fs");
    block = new Dirt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f, 0.f, 0.f), shader);



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