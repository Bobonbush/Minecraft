#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer() {
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    shaderManager->addShader("solid", "Shader/solid.vs", "Shader/solid.fs");
    
    shader = ShaderManager::GetInstance() -> getShader("solid");
}



void ChunkRenderer::add(const ChunkMesh & mesh) {
    meshes.push_back(&mesh);
}

void ChunkRenderer::render(const glm::mat4 & view, const glm::mat4 & projection) {
    
    shader -> use();
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    shader -> setVec3("viewPos", Player::GetInstance() -> getPosition());
    shader -> setVec3("lightPos", Player::GetInstance() -> getPosition() + glm::vec3(0.0f, 300.0f, 0.0f));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    //glDisable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    //glDisable(GL_BLEND);
    BlockDataBase::GetInstance() -> textureAtlas.bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(Chunk::CHUNK_SCALE, Chunk::CHUNK_SCALE, Chunk::CHUNK_SCALE));
    //model = glm::rotate(model, glm::radians((float)glfwGetTime() * 500.f), glm::vec3(1.0f, 1.0f, 0.0f));
    shader -> setMat4("model", model);

    
    for(const ChunkMesh* mesh : meshes) {
        
        const ChunkMesh & m = *mesh;
        
        m.getModel().bindVao();
        
        glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    
    meshes.clear();
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}