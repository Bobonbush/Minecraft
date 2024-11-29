#include "Texture.h"
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureAtlas.h"
#include "memory.h"


class BoxHandle {
    private:
        
        unsigned int VAO, VBO, EBO;
        unsigned int m_texture[2]; // on and off
        std::shared_ptr<Shader> m_shader;
        bool pressed[2];
        bool chosen;
};

class Inventory {
    private:
        
};