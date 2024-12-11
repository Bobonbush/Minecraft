#ifndef QUADRENDERER_H
#define QUADRENDERER_H
#include <vector>
#include <Texture&Shader/TextureAtlas.h>
#include <Texture&Shader/ShaderManager.h>
#include "Utils/Camera.h"
#include "Model.h"
#include "Algorithm.h"
#include "Item/itemDataBase.h"
class QuadRenderer {
    private:
        std::vector<glm::vec3> quads;
        std::unique_ptr<Model> quadModel;
        std::shared_ptr<Shader> shader;
        std::unique_ptr<TextureAtlas> texture;
        static QuadRenderer * instance;
        QuadRenderer();
    
    public :
        static QuadRenderer * getInstance() {
            if(instance == nullptr) {
                instance = new QuadRenderer();
            }
            return instance;
        }

        ~QuadRenderer() {
            delete instance;
        }

        void add(const glm::vec3 & position);
        void LoadData(const glm::vec2 & coords);
        void renderQuads(const glm::mat4 & view, const glm::mat4 &projection, const glm::vec3 & size);

    
};

#endif // QUADRENDERER_H