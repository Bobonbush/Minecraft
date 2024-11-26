#include "Texture.h"
#include "Texture&Shader/ShaderManager.h"


class SkyBox {
    private:
        unsigned int VAO, VBO;
        std::shared_ptr<Shader> shader;
        unsigned int textureID;
        std::vector<std::string> faces
        {
            "Assets/skybox/right.png",
            "Assets/skybox/left.png",
            "Assets/skybox/top.png",
            "Assets/skybox/bottom.png",
            "Assets/skybox/front.png",
            "Assets/skybox/back.png"
        };
    public:
        SkyBox();
        ~SkyBox();
        void render(const glm::mat4& view, const glm::mat4& projection);
};