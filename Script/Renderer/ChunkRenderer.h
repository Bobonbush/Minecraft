#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H
#include "Chunk/ChunkBuilder.h"
#include "Camera.h"
#include <Texture&Shader/TextureBind.h>
#include <Texture&Shader/ShaderManager.h>
#include "Player/Player.h"

class ChunkRenderer {
    private:
        std::vector<const ChunkMesh *> meshes;
        std::vector<const ChunkMesh *> waterMeshes;

        std::shared_ptr<Shader> shader;
        std::shared_ptr<Shader> waterShader;

    public:
        
        
        ChunkRenderer();
        void add(const ChunkMesh & mesh, const ChunkMesh & waterMesh);
        void render(const glm::mat4 & view, const glm::mat4 & projection);

        void OutputMeshes() {
            std::cout << meshes.size() << std::endl;
        }
};

#endif // CHUNKRENDERER_H