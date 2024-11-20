#include "CubeRenderer.h"


CubeRenderer::CubeRenderer() {
    cubeModel = std::make_unique<Model>();
    shader = ShaderManager::GetInstance() -> getShader("solid");  
    texture = std::make_unique<TextureAtlas>("Assets/Default pack.png");

    std::vector<GLfloat> vertices = {
                // Front
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,

                // Top

                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,

                //Bot

                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                
                //Left
                -0.5f, 0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                
                // Right
                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, 0.5f,
                
                // Behind
                -0.5f, 0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f
    };

    auto top = texture -> getTexture(glm::vec2(2, 0));
    auto side = texture -> getTexture(glm::vec2(1, 0));
    auto bottom = texture -> getTexture(glm::vec2(0, 0));
    SPA::RotateArray2f(side, 2);
    std::vector<GLfloat> texcoords;
    texcoords.insert(texcoords.begin(), side.begin(), side.end()); // Front
    
    texcoords.insert(texcoords.end(), top.begin(), top.end()); // Top
    texcoords.insert(texcoords.end(), bottom.begin(), bottom.end()); // Bottom
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Left
    SPA::RotateArray2f(side, 3);
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Right
    SPA::RotateArray2f(side, 1);
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Behind

    

    for(int i = 0 ; i < 6 * 4 * 2 ; i+= 2) {
       texcoords[i+1] = 1 - texcoords[i+1];
    }
    std::vector<GLuint> indices = {
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
    };

    cubeModel -> addData(Mesh(vertices, texcoords, indices));
}

void CubeRenderer::add(const glm::vec3 & position) {
    cubes.push_back(position);
}

void CubeRenderer::renderCubes(const glm::mat4 & view, const glm::mat4 &projection) {
    shader -> use();

    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    cubeModel -> bindVao();
    glActiveTexture(GL_TEXTURE0);
    texture -> bind();

    for(auto & cube : cubes) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cube);
        shader -> setMat4("model", model);
        glDrawElements(GL_TRIANGLES, cubeModel -> getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    cubes.clear();
}

