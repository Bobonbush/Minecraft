#ifndef HITBOX_H
#define HITBOX_H
#include "Texture&Shader/ShaderManager.h"
#include "Texture.h"


class HitBox {   // Just use to draw a hitbox
    private:
        unsigned int VAO, VBO, EBO;
        unsigned int m_texture;
        std::shared_ptr<Shader> m_shader;
    public:
        
        HitBox();
        ~HitBox();
        
        void Draw(const glm::vec3 & position,const glm::vec3 & scale, const glm::mat4 & view, const glm::mat4 & projection );
};

#endif // HITBOX_H