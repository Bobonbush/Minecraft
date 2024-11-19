#ifndef RENDERMASTER_H
#define RENDERMASTER_H
#include  "Texture&Shader/TextureBind.h"
#include "QuadRenderer.h"
#include <iostream>
class Camera;

class RenderMaster {
    public:
        RenderMaster();
        void drawQuads(const glm::vec3 & pos);

        void finishRender(const glm::mat4 & view, const glm::mat4 & projection);
    private:
        std::unique_ptr<QuadRenderer> quadRenderer;
};

#endif // RENDERMASTER_H