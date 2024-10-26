#include "ShaderLoad.h"


ShaderManager * ShaderManager::instance = nullptr;
ShaderManager::ShaderManager() {
    
}

ShaderManager::~ShaderManager() {
    delete instance;
}


void ShaderManager::LoadShader(std::string name, std::string vertexPath, std::string fragmentPath) {
    if(shaders.find(name) != shaders.end()) {
        std::cout << "Shader already exists" << '\n';
        return;
    }
    SPA::convertToLowerCase(name);

    shaders[name] = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());
}

std::shared_ptr<Shader> ShaderManager::GetShader(std::string name) {
    SPA::convertToLowerCase(name);
    if(shaders.find(name) == shaders.end()) {
        std::cout << "Shader not found" << '\n';
       // return *shaders["default"];
    }
    
    return shaders[name];
}
   


