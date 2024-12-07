#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Texture.h"
#include "Utils/Singleton.h"

// This class is used to render textures on the screen including animations
class SpriteRenderer : Singleton {
    private :
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int quadEBO;
    static SpriteRenderer * instance;

    std::shared_ptr<Shader> shader;
    
    SpriteRenderer();
    

    public:

    static SpriteRenderer * getInstance() {
        if(instance == nullptr) {
            instance = new SpriteRenderer();
        }
        return instance;
    }

    ~SpriteRenderer() {
        glDeleteVertexArrays(1, &quadVAO);
        glDeleteBuffers(1, &quadVBO);
        glDeleteBuffers(1, &quadEBO);
        delete instance;
    }
    void DrawSprite(unsigned int texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, glm::mat4 view , glm::mat4 projection);
    void initRenderData(int pivot = 0);

    void setShader(std::shared_ptr<Shader> _shader) {
        shader = _shader;
    }
    
};


#endif