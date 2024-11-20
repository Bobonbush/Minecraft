#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "Shader.h"
#include "Singleton.h"
#include <map>
#include <memory>
class ShaderManager {
    std::map<std::string, std::shared_ptr<Shader>> shaders;
    static ShaderManager * instance;
    ShaderManager() = default;
    public:

    static ShaderManager * GetInstance() {
        if(instance == nullptr) {
            instance = new ShaderManager();
        }
        return instance;
    }

    void addShader(const std::string & name, const std::string & vertexPath, const std::string & fragmentPath);

    std::shared_ptr<Shader> getShader(const std::string & name) ;

    ~ShaderManager() {
        delete instance;
    }

};

#endif // SHADERMANAGER_H