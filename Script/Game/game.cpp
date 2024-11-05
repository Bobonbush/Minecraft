#include "game.h"








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
    elapsedTime += deltaTime;
    glm::mat4 view = player -> getViewMatrix();
    glm::mat4 projection = player -> getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y);
    
    /*
    std::cout << "The view matrix is : " << '\n';
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            std::cout << view[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "The projection matrix is : " << '\n';
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            std::cout << projection[i][j] << ' ';
        }
        std::cout << '\n';
    }
    */
    
    world -> Update(deltaTime, view, projection);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastTime = totalTime;


    world -> Render(view, projection);
    player -> Update(deltaTime, world -> getValidBodies());

    accumulatedTime += deltaTime;
    while(accumulatedTime >= maxFrameTime) {
        FixedUpdate(xpos, ypos);
        accumulatedTime -= maxFrameTime;
    }
    Alpha = accumulatedTime / maxFrameTime;

}

void Game::FixedUpdate(float xpos, float ypos) {
    player -> FixedUpdate( window,xpos, ypos, world -> getValidBodies(), Alpha);
}

void Game::Render() {
    glm::mat4 view = player -> getViewMatrix();
    glm::mat4 projection = player -> getProjectionMatrix(Setting::getInstance() -> getResolution().x, Setting::getInstance() -> getResolution().y);
    player -> Render();
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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Culls back faces by default
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    
    glViewport(0, 0, settings -> getResolution().x , settings -> getResolution().y);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
}

void Game::Run() {
    Init();
    player = Player::getInstance();
    world = WorldRenderer::getInstance();
    
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f , 0.7f , 1.f);
        Update();
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }


    glfwTerminate();

}