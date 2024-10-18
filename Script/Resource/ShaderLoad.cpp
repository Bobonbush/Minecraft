#include "ShaderLoad.h"


ShaderManager * ShaderManager::instance = nullptr;
ShaderManager::ShaderManager() {
    
}

ShaderManager::~ShaderManager() {
    for (auto shader : shaders) {
        delete shader.second;
    }
    delete instance;
}


void ShaderManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath) {
    ;
    SPA::convertToLowerCase(name);
    shaders[name] = new Shader(vertexPath.c_str(), fragmentPath.c_str());
}

Shader & ShaderManager::GetShader(std::string name) {
    SPA::convertToLowerCase(name);
    return *shaders[name];
}
   


