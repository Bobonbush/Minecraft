#include "InteractiveBox.h"

std::unique_ptr<TextHandler> InventoryBox::textLoader = nullptr;

InventoryBox::InventoryBox(glm::vec2 position, glm::vec2 size, int number) : m_position(position), m_size(size), number(number) {
    TextureManager * textureManager = TextureManager::getInstance();
    m_texture[0] = textureManager -> getTexture("Assets/Inventory/off.png");
    m_texture[1] = textureManager -> getTexture("Assets/Inventory/on.png");
    m_spriteRenderer = SpriteRenderer::getInstance();
    if(textLoader == nullptr) {
        textLoader = std::make_unique<TextHandler>();
        textLoader -> LoadFont("Assets/Font/Revamped.ttf", 12);
    }
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
    Config * config = Config::GetInstance();

    if(!empty) {
        item -> Render();
        int number = item -> getNumber();
        textLoader -> RenderMiddleText(SPA::convertNumberToString(number), m_position.x + m_size.x/2.75f , m_position.y + m_size.y /2.75f, 2.f, glm::vec3(0.f), 0.f, glm::vec2(config -> GetWidth(), config -> GetHeight()));
    }
    
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    m_spriteRenderer -> setShader(shaderManager -> getShader("Screen"));
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    m_spriteRenderer -> DrawSprite(m_texture[m_chosen], m_position, m_size, 0.f, glm::vec3(1.f), view , projection);
    m_chosen = false;
    
} 

