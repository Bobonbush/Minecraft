#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer() {
    ShaderManager::GetInstance() -> addShader("ChunkShader", "Shader/Chunk.vs", "Shader/Chunk.fs");
    shader = ShaderManager::GetInstance() -> getShader("ChunkShader");
}

void ChunkRenderer::add(const ChunkMesh & mesh) {
    meshes.push_back(&mesh);
}

void ChunkRenderer::render(const glm::mat4 & view, const glm::mat4 & projection) {
    shader -> use();
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);

    BlockDataBase::GetInstance() -> textureAtlas.bind();

    for(const ChunkMesh* mesh : meshes) {
        const ChunkMesh & m = *mesh;

        m.getModel().bindVao();
        glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, 0);

    }
    meshes.clear();
}