#include "QuadRenderer.h"

QuadRenderer::QuadRenderer() {
    quadModel = std::make_unique<Model>();

    
    quadModel -> addData(
        Mesh(
            {
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,

                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,

                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,

                -0.5f, 0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,

                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, 0.5f,

                -0.5f, 0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f
            },
            
            {
                1.0f , 1.0f,
                1.0f, 0.0f, 
                0.0f, 0.0f,
                0.0f, 1.0f,

                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,

                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
                0.0f, 1.0f,

                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
                0.0f, 1.0f,

                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
                0.0f, 1.0f,

                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f,
                0.0f, 1.0f
            },
            {
                0, 1, 3,
                1, 2, 3,
                4, 5, 7,
                5, 6, 7,
                8, 9, 11,
                9, 10, 11,
                12, 13, 15,
                13, 14, 15,
                16, 17, 19,
                17, 18, 19,
                20, 21, 23,
                21, 22, 23

            }
        )
    );

    

    ShaderManager * shaderManager = ShaderManager::GetInstance();
    shaderManager->addShader("solid", "Shader/solid.vs", "Shader/solid.fs");
    shader = shaderManager->getShader("solid");
    texture = std::make_unique<TextureBind>("Assets/dirt.png");

    
}

void QuadRenderer::add(const glm::vec3 & position) {
    quads.push_back(position);
}

void QuadRenderer::renderQuads(const glm::mat4 & view, const glm::mat4 &projection) {

    shader -> use();


    quadModel -> bindVao();
    glActiveTexture(GL_TEXTURE0);
    texture -> bind();
    
    shader -> setMat4("view", view);


    shader -> setMat4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    shader -> setMat4("model", model);

    for(auto & quad : quads) {
        
        model = glm::mat4(1.0f);
        //model = glm::translate(model, quad);
        //model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50), glm::vec3(1.0f, 0.0f, 1.0f));

        //shader -> setMat4("model", model);

        glDrawElements(GL_TRIANGLES, quadModel -> getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    


}