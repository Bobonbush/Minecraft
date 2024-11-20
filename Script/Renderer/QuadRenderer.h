#ifndef QUADRENDERER_H
#define QUADRENDERER_H
#include <vector>
#include <Texture&Shader/TextureBind.h>
#include <Texture&Shader/ShaderManager.h>
#include "Utils/Camera.h"
#include "Model.h"
class QuadRenderer {
    private:
        std::vector<glm::vec3> quads;
        std::unique_ptr<Model> quadModel;
        std::shared_ptr<Shader> shader;
        std::unique_ptr<TextureBind> texture;

        
    
    public :
        QuadRenderer();

        void add(const glm::vec3 & position);

        void renderQuads(const glm::mat4 & view, const glm::mat4 &projection);

    
};

#endif // QUADRENDERER_H