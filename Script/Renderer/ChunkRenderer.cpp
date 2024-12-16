#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer() {
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    shaderManager->addShader("solid", "Shader/solid.vs", "Shader/solid.fs");
    
    shader = ShaderManager::GetInstance() -> getShader("solid");
    shaderManager -> addShader("water", "Shader/water.vs", "Shader/water.fs");
    waterShader = ShaderManager::GetInstance() -> getShader("water");
}



void ChunkRenderer::add(const ChunkMesh & mesh, const ChunkMesh & waterMesh) {
    if(mesh.has_mesh)
        meshes.push_back(&mesh);
    if(waterMesh.has_mesh)
        waterMeshes.push_back(&waterMesh);
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
    
    glDisable(GL_CULL_FACE);
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




    waterShader -> use();
    waterShader -> setMat4("view", view);
    waterShader -> setMat4("projection", projection);
    waterShader -> setVec3("viewPos", Player::GetInstance() -> getPosition());
    waterShader -> setVec3("lightPos", Player::GetInstance() -> getPosition() + glm::vec3(0.0f, 300.0f, 0.0f));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    BlockDataBase::GetInstance() -> textureAtlas.bind();
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(Chunk::CHUNK_SCALE, Chunk::CHUNK_SCALE, Chunk::CHUNK_SCALE));

    shader -> setMat4("model", model);
    for(const ChunkMesh* mesh : waterMeshes) {
        
        const ChunkMesh & m = *mesh;
        
        m.getModel().bindVao();
        
        glDrawElements(GL_TRIANGLES, m.getModel().getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    waterMeshes.clear();
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);

}