#include "Config.h"

Config* Config::instance = nullptr;

void Config::SetVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Elden Craft", NULL, NULL);
    
    if(!window) {
        std::cout << "Failed to create window" << std::endl;
        return;
    }
    srand(time(NULL));
    seed = rand();
    seed = 15324;
    glfwMakeContextCurrent(window);
}
void Config::ChangeConfig() {
    
    //glfwWindowHint(GLFW_SAMPLES, antialiasing);
    //glfwWindowHint(GLFW_DEPTH_BITS, depthBits);
    //glfwWindowHint(GLFW_STENCIL_BITS, stencilBits);

    glfwSetWindowSize(window, width, height);
    glViewport(0, 0, width, height);
}

void Config::ReadConfig() {
    File * file = File::GetInstance();
    file -> SetJson("Assets/config/config.json");
    width = file -> GetJsonFloat("width");
    height = file -> GetJsonFloat("height");

    antialiasing = file -> GetJsonInt("antialiasing");
    depthBits = file -> GetJsonInt("depthBits");
    stencilBits = file -> GetJsonInt("stencilBits");
}