#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "Shader.h"
#include <map>
#include "Algorithm.h"

#include <memory>

class ShaderManager  {
    private:
        static ShaderManager * instance;
        std::map<std::string, std::shared_ptr<Shader>> shaders;
        ShaderManager();
    public:
        ~ShaderManager();
        
        void LoadShader(std::string name, std::string vertexPath, std::string fragmentPath);

        static ShaderManager* getInstance() {
            if (instance == nullptr) {
                instance = new ShaderManager();
            }
            return instance;
        }

        std::shared_ptr<Shader> GetShader(std::string name);
};

#endif