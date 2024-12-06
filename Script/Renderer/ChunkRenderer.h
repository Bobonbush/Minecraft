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

        std::shared_ptr<Shader> shader;

    public:
        
        
        ChunkRenderer();
        void add(const ChunkMesh & mesh);
        void render(const glm::mat4 & view, const glm::mat4 & projection);

        void OutputMeshes() {
            std::cout << meshes.size() << std::endl;
        }
};

#endif // CHUNKRENDERER_H