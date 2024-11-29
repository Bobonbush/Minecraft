#include "hitbox.h"


HitBox::HitBox() {
    float vertices[] = {
        -0.5f, 0.5f, 0.5f,   1.0f, 1.0f, // top right
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top left

        0.5f, -0.5f, 0.5f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // top left

        -0.5f, 0.5f, 0.5f,   1.0f, 1.0f, // top right
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // top left

        0.5f, 0.5f, 0.5f,   1.0f, 1.0f, // top right
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // top left

        0.5f, 0.5f, 0.5f,   1.0f, 1.0f, // top right
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top left

        -0.5f, -0.5f, 0.5f,   1.0f, 1.0f, // top right
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f  // top left


    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle

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

    ShaderManager::GetInstance() -> addShader("outbound", "Shader/outbound.vs", "Shader/outbound.fs");

    m_shader = ShaderManager::GetInstance() -> getShader("outbound");

    m_texture = TextureLoader::LoadTexture("Assets/hitbox.png");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

HitBox::~HitBox() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void HitBox::Draw(const glm::vec3 & position, const glm::vec3 &scale, const glm::mat4 & view, const glm::mat4 & projection) {
    m_shader -> use();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glActiveTexture(GL_TEXTURE0);
    m_shader -> setInt("uTexture", 0);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    m_shader -> setMat4("model", model);
    m_shader -> setMat4("view", view);
    m_shader -> setMat4("projection", projection);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}