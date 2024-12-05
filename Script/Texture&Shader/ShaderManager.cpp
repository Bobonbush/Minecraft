#include "ShaderManager.h"

ShaderManager * ShaderManager::instance = nullptr;

void ShaderManager::addShader(const std::string & name, const std::string & vertexPath, const std::string & fragmentPath) {
    if(shaders.find(name) != shaders.end()) {
        //std::cout << "Shader already exists" << std::endl;
        return ;
    }
    shaders[name] = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string &name) {
        if(shaders.find(name) == shaders.end()) {
            std::cout << "Shader not found" << std::endl;
            return nullptr;
        }
        return shaders[name];
}