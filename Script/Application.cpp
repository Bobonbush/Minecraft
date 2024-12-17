#include "Application.h"

Application* Application::instance = nullptr;

Application::Application() {
    config = Config::GetInstance();
    Init();
}

Application::~Application() {
    
    glfwTerminate();
}


void Application::Init() {
    if(!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    config -> ReadConfig();
    config -> SetVersion();

    

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    




    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    /*
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Culls back faces by default
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    */
    config -> ChangeConfig();
    //state = std::make_unique<PlayingState>();

    Block::initBlockMap();

}


void Application::Update(float deltaTime) {
    states.Update(deltaTime);
}

void Application::Render( ) {
    states.render();
}

void Application::FixedUpdate(float xpos, float ypos) {
    states.FixedUpdate(xpos, ypos);
}

void Application::Run() {

    states.pushState(std::make_unique<World>());
    float totalTime = 0;
    int FPS = 0;
    int cnt = 0;
    while(!glfwWindowShouldClose(config -> GetWindow())) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.5f , 0.7f , 1.f);
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        float currentTime = glfwGetTime();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        totalTime += elapsedTime;
        FPS++;
        if (totalTime >= 1.0f) {
            std::cout << "FPS: " << FPS << std::endl;
            std::cout << "COUNT: " << cnt << std::endl;
            FPS = 0;
            totalTime = 0;
            cnt = 0;
        }

        accumulator += elapsedTime;

        double xpos, ypos;
        
        glfwGetCursorPos(config -> GetWindow(), &xpos, &ypos);
        float x = xpos;
        float y = ypos;

        float width = config -> GetWidth();
        float height = config -> GetHeight();
        

        if(lastX == -192313.0f) {
            lastX = xpos;   
            lastY = ypos;
        }

        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        
        lastX = xpos;
        lastY = ypos;

        
        while(accumulator >= maxFrameTime) {
            accumulator -= maxFrameTime;
            cnt++;
            FixedUpdate(xoffset, yoffset);
        }
        Alpha = accumulator / maxFrameTime;
        Update(elapsedTime);
        Render();

        
        

        Alpha = accumulator / maxFrameTime;

        glfwSwapBuffers(config -> GetWindow());
        glfwPollEvents();
    }
}

