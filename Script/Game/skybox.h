#include "Utils/Texture.h"
#include "Resource/ShaderLoad.h"
#include "Resource/TextureLoad.h"
#include "Player.h"
#include "settings.h"

class Planet {
    private:
        std::unique_ptr<CubeSurface> cubeRenderer;
        unsigned int texture;
        glm::vec3 position;
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::vec3 TimeZone = glm::vec3(0.0f, 0.0f, 0.0f);

        const float distance = 75.0f;
    public :
        Planet(std::shared_ptr<Shader> shader,char *path, glm::vec3 TimeZone);
        ~Planet();
        void Render(glm::mat4 view, glm::mat4 projection);
};

class Skybox {
    private:
        unsigned int VAO, VBO;
        std::shared_ptr<Shader> shader;
        unsigned int texture;
        std::unique_ptr<Planet> sun;
        std::unique_ptr<Planet> moon;

    public:
        Skybox();
        ~Skybox();
        void Render(glm::mat4 view, glm::mat4 projection);
};