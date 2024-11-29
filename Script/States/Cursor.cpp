#include "Cursor.h"


Cursor * Cursor::m_instance = nullptr;
Cursor::Cursor() {
    float vertices[] = {
        // positions          // texture coords
        0.5f, 0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_texture = TextureLoader::LoadTexture("Assets/cursor.png");
    ShaderManager::GetInstance() -> addShader("Screen", "Shader/Screen.vs", "Shader/Screen.fs");
    m_shader = ShaderManager::GetInstance() -> getShader("Screen");
    m_shader -> use();
    m_shader -> setInt("uTexture", 0);

    for(int i = 0 ; i < 2 ; i++) {
        pressed[i] = false;
    }
}

Cursor::~Cursor() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete m_instance;
}

void Cursor::Draw( const float halfX , const float halfY) {
    m_shader -> use();
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.075f * halfY / halfX, 0.075f, 0.075f));
   // model = glm::translate(model, glm::vec3(halfX, halfY, 0.0f));
    m_shader -> setMat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Cursor::GetInput() {
    if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if(pressed[MOUSE_BUTTONS::LEFT] == false) {
            pressed[MOUSE_BUTTONS::LEFT] = true;
            return MOUSE_EVENT::LEFT_CLICK;
        } else {
            return MOUSE_EVENT::LEFT_HOLD;
        }
    } else {
        if(pressed[LEFT] == true) {
            pressed[LEFT] = false;
            return MOUSE_EVENT::LEFT_RELEASE;
        }
    }


    if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if(pressed[MOUSE_BUTTONS::RIGHT] == false) {
            pressed[MOUSE_BUTTONS::RIGHT] = true;
            return MOUSE_EVENT::RIGHT_CLICK;
        } else {
            return MOUSE_EVENT::RIGHT_HOLD;
        }
    } else {
        if(pressed[MOUSE_BUTTONS::RIGHT] == true) {
            pressed[MOUSE_BUTTONS::RIGHT] = false;
            return MOUSE_EVENT::RIGHT_RELEASE;
        }
    }

    return -1;
}