#include "Application.h"

Application::Application() {
    window = nullptr;
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1000, 800, "Elden Craft", NULL, NULL);
    if(!window) {
        std::cout << "Failed to create window" << std::endl;
        //glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

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

    glViewport(0, 0, 1000, 800);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}


void Application::Update() {
}

void Application::Render() {

}

void Application::FixedUpdate(float xpos, float ypos) {

}

void Application::Run() {
    while(!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f , 0.7f , 1.f);
        float currentTime = glfwGetTime();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += elapsedTime;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        while(accumulator >= maxFrameTime) {
            accumulator -= maxFrameTime;
            FixedUpdate(xpos, ypos);
        }

        Alpha = accumulator / maxFrameTime;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

