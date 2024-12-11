#ifndef RENDERMASTER_H
#define RENDERMASTER_H
#include  "Texture&Shader/TextureBind.h"
#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "Skybox.h"
#include <iostream>
class Camera;

class RenderMaster {
    public:
        RenderMaster();
        void drawQuads(const glm::vec3 & pos);
        void drawCubes(const glm::vec3 & pos);
        void drawChunk(const ChunkMesh & mesh);

        void finishRender(const glm::mat4 & view, const glm::mat4 & projection);
    private:
        std::unique_ptr<ChunkRenderer> chunkRenderer;
        std::unique_ptr<SkyBox> skybox;
};

#endif // RENDERMASTER_H