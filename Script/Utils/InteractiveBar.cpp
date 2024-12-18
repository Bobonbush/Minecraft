#include "InteractiveBar.h"



InteractiveBar::InteractiveBar(const int MaxHealth, const glm::vec2 & position, const glm::vec2 & size, const std::string &full, const std::string &empty) : position(position), size(size) {
    maxHealth = MaxHealth;
    health = maxHealth;
    spriteRenderer = SpriteRenderer::getInstance();
    TextureManager * textureManager = TextureManager::getInstance();
    texture[0] = textureManager -> getTexture(full.c_str());
    texture[1] = textureManager -> getTexture(empty.c_str());

    float aspect = 1.f/ Config::GetInstance() -> GetAspectRatio();

    this -> size.x *= aspect;
}


InteractiveBar::~InteractiveBar() {
}

void InteractiveBar::Render() {
    Config * config = Config::GetInstance();
    glDisable(GL_DEPTH_TEST);
    
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    spriteRenderer -> setShader(shaderManager -> getShader("Screen"));
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    const float offset = 0.05f * size.x;
    for(int i = 0; i < maxHealth; i++) {
        glm::vec2 pos = glm::vec2(position.x + i * size.x + offset * i, position.y);
        spriteRenderer -> DrawSprite(texture[i >= health], pos, size, 0.f, glm::vec3(1.f), view , projection);
    }
    
    glEnable(GL_DEPTH_TEST);
}

void InteractiveBar::setHealth(int _health) {
    health = _health;
}

int InteractiveBar::getHealth() const {
    return health;
}