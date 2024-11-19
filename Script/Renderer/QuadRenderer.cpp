#include "QuadRenderer.h"

QuadRenderer::QuadRenderer() {
    quadModel.addData(
        Mesh(
            {
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
            },
            
            {
                1.0f , 1.0f,
                1.0f, 0.0f, 
                0.0f, 0.0f,
                0.0f, 1.0f
            },
            {
                0, 1, 3,
                1, 2, 3
            }
        )
    );

    ShaderManager * shaderManager = ShaderManager::GetInstance();
    shaderManager->addShader("solid", "Shader/solid.vs", "Shader/solid.fs");
    shader = shaderManager->getShader("solid");
    texture = TextureBind("Assets/dirt.png");

    
}

void QuadRenderer::add(const glm::vec3 & position) {
    quads.push_back(position);
}

void QuadRenderer::renderQuads(const glm::mat4 & view, const glm::mat4 &projection) {
    shader -> use();
    quadModel.bindVao();
    texture.bind();

    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    shader -> setMat4("model", model);

    for(auto & quad : quads) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, quad);
        shader -> setMat4("model", model);

        glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }


}