#include "AnimationBoxRenderer.h"


AnimationBox::AnimationBox(const int & maxFrame, const std::string &path, const int& imageSize) : maxFrame(maxFrame) {
    ShaderManager::GetInstance() -> addShader("outbound", "Shader/outbound.vs", "Shader/outbound.fs");
    m_shader = ShaderManager::GetInstance() -> getShader("outbound");
    texture = std::make_unique<TextureAtlas>(path);
    texture -> setIndividualTextureSize(imageSize);
    frame = 0;
    
    glm::vec2 coords = glm::vec2(0.f, 0.f);
    cubeModel.resize(maxFrame);
    for(int i = 0 ; i < maxFrame ; i++) {
        LoadData(cubeModel[i], coords);
        coords.x += 1.f;
    }
}

AnimationBox::~AnimationBox() {
}

void AnimationBox::LoadData(Model & model, const glm::vec2 & coords) {
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

    auto top = texture -> getTexture(coords);
    auto side = texture -> getTexture(coords);
    auto bottom = texture -> getTexture(coords);
   //SPA::RotateArray2f(side, 2);
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

    model.addData(Mesh(vertices, texcoords, indices));

}


void AnimationBox::GetFrame(float currentTime, float maxTime) {
    float one_frame = maxTime / maxFrame;
    frame = (int) (currentTime / one_frame);
    frame = frame % maxFrame;
}

void AnimationBox::Render(const glm::vec3 & position, const glm::vec3 & scale, const float currentTime, const float maxTime, const glm::mat4 & view, const glm::mat4 & projection) {
    GetFrame(currentTime, maxTime);
    cubeModel[frame].bindVao();

    glActiveTexture(GL_TEXTURE0);
    texture -> bind();

    
    m_shader -> use();
    m_shader -> setMat4("view", view);
    m_shader -> setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    m_shader -> setMat4("model", model);

    glDrawElements(GL_TRIANGLES, cubeModel[frame].getIndicesCount(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}