#ifndef ANIMATIONBOXRENDERER_H
#define ANIMATIONBOXRENDERER_H
#include "Texture&Shader/ShaderManager.h"
#include "Texture.h"
#include "Texture&Shader/TextureManager.h"
#include "Model.h"
#include "Texture&Shader/TextureAtlas.h"
#include "Algorithm.h"
class AnimationBox {
    private:
        std::shared_ptr<Shader> m_shader;
        std::vector<Model> cubeModel;
        std::unique_ptr<TextureAtlas> texture;
        int frame;
        int maxFrame;


        void LoadData(Model & model, const glm::vec2 & coords);
        void GetFrame(float currentTime, float maxTime);
    public:
        AnimationBox(const int  & maxFrame, const std::string &path, const int & imageSize);
        ~AnimationBox();

        
        void Render(const glm::vec3 & position, const glm::vec3 & scale, const float currentTime, const float maxTime, const glm::mat4 & view, const glm::mat4 & projection);
};

#endif // ANIMATIONBOXRENDERER_H