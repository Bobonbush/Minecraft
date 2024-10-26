#include "Utils/Texture.h"
#include "Resource/ShaderLoad.h"

class Skybox {
    private:
        unsigned int VAO, VBO;
        std::shared_ptr<Shader> shader;
        unsigned int texture;
    public:
        Skybox();
        ~Skybox();
        void Render(glm::mat4 view, glm::mat4 projection);
};