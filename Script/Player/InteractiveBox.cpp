#include "InteractiveBox.h"

InventoryBox::InventoryBox(glm::vec2 position, glm::vec2 size, int number) : m_position(position), m_size(size), number(number) {
    TextureManager * textureManager = TextureManager::getInstance();
    m_texture[0] = textureManager -> getTexture("Assets/Inventory/off.png");
    m_texture[1] = textureManager -> getTexture("Assets/Inventory/on.png");
    m_spriteRenderer = SpriteRenderer::getInstance();
}

InventoryBox::~InventoryBox() {
    
}

void InventoryBox::update() {
    if(item != nullptr) {

    
        item -> update();
        item -> setPosition(glm::vec3(m_position, 0.f));
    }
}

void InventoryBox::Render() {
    if(!empty) 
        item -> Render();
    
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    m_spriteRenderer -> setShader(shaderManager -> getShader("Screen"));
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    m_spriteRenderer -> DrawSprite(m_texture[m_chosen], m_position, m_size, 0.f, glm::vec3(1.f), view , projection);
    m_chosen = false;
    
} 

