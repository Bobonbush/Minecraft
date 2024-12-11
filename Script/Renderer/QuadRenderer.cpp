#include "QuadRenderer.h"


QuadRenderer * QuadRenderer::instance = nullptr;

QuadRenderer::QuadRenderer() {
    quadModel = std::make_unique<Model>();

    
    ShaderManager::GetInstance() -> addShader("Screen", "Shader/Screen.vs", "Shader/Screen.fs");
    shader = ShaderManager::GetInstance() -> getShader("Screen");  
    texture = std::make_unique<TextureAtlas>("Assets/Items/items.png");
    
}

void QuadRenderer::LoadData(const glm::vec2 &coords) {
    std::vector<GLfloat> vertices = {
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    auto textureCoords = ItemDataBase::GetInstance() -> textureAtlas.getTexture(coords);

    std::vector<GLfloat> texcoords;

    texcoords.insert(texcoords.begin(), textureCoords.begin(), textureCoords.end());

    for(int i = 0 ; i < 4 * 2 ; i+= 2) {
        texcoords[i+1] = 1 - texcoords[i+1];
    }

    std::vector<GLuint> indices = {
        0, 1, 3,
        1, 2, 3
    };

    quadModel -> addData(Mesh(vertices, texcoords, indices));
    
}

void QuadRenderer::add(const glm::vec3 & position) {
    quads.push_back(position);
}

void QuadRenderer::renderQuads(const glm::mat4 & view, const glm::mat4 &projection, const glm::vec3 & size) {

    shader -> use();


    quadModel -> bindVao();
    glActiveTexture(GL_TEXTURE0);
    texture -> bind();
    
    shader -> setMat4("view", view);


    shader -> setMat4("projection", projection);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    shader -> setMat4("model", model);

    for(auto & quad : quads) {
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, quad);
        //model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50), glm::vec3(1.0f, 0.0f, 1.0f));
        
        model = glm::scale(model, size);
        //shader -> setMat4("model", model);

        glDrawElements(GL_TRIANGLES, quadModel -> getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    glDisable(GL_DEPTH_TEST);


    glBindVertexArray(0);
    quads.clear();
    


}