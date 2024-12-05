#include "SpriteRenderer.h"

SpriteRenderer * SpriteRenderer::instance = nullptr;
SpriteRenderer::SpriteRenderer(){
    this -> initRenderData(4);
}

void SpriteRenderer::initRenderData(int pivot) {
    /*
    pivot = 0 : Bottom left
    pivot = 1 : Bottom right
    pivot = 2 : Top left
    pivot = 3 : Top right
    pivot = 4 : Center

    */
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 
    
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer :: DrawSprite(unsigned int texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, glm::mat4 view , glm::mat4 projection){
    this -> shader -> use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));
    shader -> setMat4("model", model);
    shader -> setVec3("spriteColor", color);
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}