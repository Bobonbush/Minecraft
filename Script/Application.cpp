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
    /*
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Culls back faces by default
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    */
    config -> ChangeConfig();

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    renderMaster = std::make_unique<RenderMaster>();
    glfwSetInputMode(config -> GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        camera -> ProcessKeyboard(FORWARD, elapsedTime);
    }
    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        camera -> ProcessKeyboard(BACKWARD, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        camera -> ProcessKeyboard(LEFT, elapsedTime);
    }

    if(glfwGetKey(config -> GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        camera -> ProcessKeyboard(RIGHT, elapsedTime);
    }
}

void Application::Run() {
    renderMaster -> drawQuads(glm::vec3(0.0f, 0.0f, 0.0f));
    while(!glfwWindowShouldClose(config -> GetWindow())) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f , 0.7f , 1.f);
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        glm::mat4 view = camera -> GetViewMatrix();
        //iew = glm::mat4(1.0f);
       
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), config -> GetWidth() / config -> GetHeight(), 0.1f, 100.0f);
        float currentTime = glfwGetTime();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += elapsedTime;
        double xpos, ypos;
        
        glfwGetCursorPos(config -> GetWindow(), &xpos, &ypos);

        if(lastX == -192313.0f) {
            lastX = xpos;   
            lastY = ypos;
        }

        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        
        lastX = xpos;
        lastY = ypos;
        Update();
        Render(view, projection);
        while(accumulator >= maxFrameTime) {
            accumulator -= maxFrameTime;
            FixedUpdate(xoffset, yoffset);
        }

        Alpha = accumulator / maxFrameTime;

        glfwSwapBuffers(config -> GetWindow());
        glfwPollEvents();
    }
}

