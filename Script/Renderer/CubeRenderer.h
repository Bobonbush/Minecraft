#ifndef CUBERENDERER_H
#define CUBERENDERER_H
#include <vector>
#include <Texture&Shader/TextureAtlas.h>
#include <Texture&Shader/ShaderManager.h>
#include "Utils/Camera.h"
#include "Model.h"
#include  "Algorithm.h"

class CubeRenderer {
    private:
        std::vector<glm::vec3> cubes;
        std::unique_ptr<Model> cubeModel;
        std::shared_ptr<Shader> shader;
        std::unique_ptr<TextureAtlas> texture;

        
    public :
        CubeRenderer();

        void add(const glm::vec3 & position);

        void renderCubes(const glm::mat4 & view, const glm::mat4 &projection);

    
};

#endif // CUBERENDERER_H