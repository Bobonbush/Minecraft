#ifndef CUBERENDERER_H
#define CUBERENDERER_H
#include <vector>
#include <Texture&Shader/TextureAtlas.h>
#include <Texture&Shader/ShaderManager.h>
#include "Utils/Camera.h"
#include "Model.h"
#include  "Algorithm.h"
#include "Utils/Singleton.h"
#include "Block/BlockDataBase.h"
class CubeRenderer : public Singleton {
    private:
        std::vector<glm::vec3> cubes;
        std::unique_ptr<Model> cubeModel;
        std::shared_ptr<Shader> shader;
        std::unique_ptr<TextureAtlas> texture;
        static CubeRenderer * instance;
        CubeRenderer();
    public :
        static CubeRenderer * getInstance() {
            if(instance == nullptr) {
                instance = new CubeRenderer();
            }
            return instance;
        }
        ~CubeRenderer() {
            delete instance;
        }
        void add(const glm::vec3 & position);
        void LoadData(const glm::vec2 & topCoords, const glm::vec2 & sideCoords, const glm::vec2 & bottomCoords);

        void renderCubes(const glm::mat4 & view, const glm::mat4 &projection, const glm::vec3 & size);

    
};

#endif // CUBERENDERER_H