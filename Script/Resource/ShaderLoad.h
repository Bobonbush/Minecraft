#include "Shader.h"
#include <map>
#include "Algorithm.h"

class ShaderManager  {
    private:
        static ShaderManager * instance;
        std::map<std::string, Shader*> shaders;
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

        Shader& GetShader(std::string name);
};