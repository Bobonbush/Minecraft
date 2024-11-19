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
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Culls back faces by default
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    config -> ChangeConfig();

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, -0.0f));
    renderMaster = std::make_unique<RenderMaster>();
    //state = std::make_unique<PlayingState>();
}


void Application::Update() {
    
}

void Application::Render(const glm::mat4 & view, const glm::mat4 &projection ) {
    //state -> render(renderMaster);
    renderMaster -> finishRender(view, projection);
    
}

void Application::FixedUpdate(float xpos, float ypos) {
    camera -> ProcessMouseMovement(xpos , ypos);
}

void Application::Run() {
    renderMaster -> drawQuads(glm::vec3(0.0f, 0.0f, 0.0f));
    while(!glfwWindowShouldClose(config -> GetWindow())) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f , 0.7f , 1.f);
        glm::mat4 view = camera -> GetViewMatrix();
        view = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera -> Zoom), (float)config -> GetWidth() / (float)config -> GetHeight(), 0.1f, 100.0f);
        projection = glm::mat4(1.0f);
        
        float currentTime = glfwGetTime();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += elapsedTime;
        double xpos, ypos;
        glfwGetCursorPos(config -> GetWindow(), &xpos, &ypos);
        Update();
        Render(view, projection);
        while(accumulator >= maxFrameTime) {
            accumulator -= maxFrameTime;
            FixedUpdate(xpos, ypos);
        }

        Alpha = accumulator / maxFrameTime;
        glfwSwapBuffers(config -> GetWindow());
        glfwPollEvents();
    }
}

