#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "Texture&Shader/ShaderManager.h"
#include "Texture.h"


class Light {
    private:
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
        std::shared_ptr<Shader> shader;
    public :

        Light(const glm::vec3 & position, const glm::vec3 & color, float intensity) : position(position), color(color), intensity(intensity) {
            shader = ShaderManager::GetInstance() -> getShader("solid");
        }

        void update() {
            shader -> use();
            shader -> setVec3("lightColor", color);
            shader -> setFloat("intensity", intensity);
            shader -> setVec3("lightPos", position);
        }

};
#endif