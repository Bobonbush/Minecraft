#include "UIUtil.h"


UITextHandler::UITextHandler(const std::string &content, const std::string &path, const glm::vec2 &position, const float &scale, const float &FontSize, const glm::vec3 &color) : position(position), scale(scale), FontSize(FontSize), color(color) {
    
    textHandler = std::make_unique<TextHandler>();
    int size = (int)FontSize;
    textHandler -> LoadFont(path.c_str(), size);
    this -> content = content;
}

UITextHandler::~UITextHandler() {
}

void UITextHandler::render() {
    Config * config = Config::GetInstance();
    textHandler -> RenderMiddleText(content, position.x, position.y, scale, color, 0.0f, glm::vec2(config -> GetWidth(), config -> GetHeight()));
}


TextAnimator::TextAnimator(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float & fontSize, const float &fontScale, const glm::vec3 & color) {
    textHandler = std::make_unique<UITextHandler>(content, path, position, fontScale, fontSize, color);
    
}

TextAnimator::~TextAnimator() {
}

AppearText::AppearText(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float & fontSize, const float & fontScale, const glm::vec3 & color) : TextAnimator(content, path, position, size, fontSize, fontScale, color) {
    alphaSpeed = 0.05f;
}

AppearText::~AppearText() {

}

void AppearText::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    alphaSpeed += 0.25f * deltaTime ;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
    }
}

void AppearText::render() {
    ShaderManager::GetInstance() -> getShader("text") -> use();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", alpha);
    textHandler -> render();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", 1.0f);
}

bool AppearText::isFinished() {
    return alpha >= 1.0f;
}

ReAppearingText::ReAppearingText(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float & fontSize, const float & fontScale, const glm::vec3 & color) : TextAnimator(content, path, position, size, fontSize, fontScale, color) {
    textHandler = std::make_unique<UITextHandler>(content, path, position, fontScale, fontSize, color);
    alphaSpeed = 0.75f;
}

ReAppearingText::~ReAppearingText() {

}

void ReAppearingText::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
        alphaSpeed = -alphaSpeed;
    }
    if(alpha <= 0.0f) {
        alpha = 0.0f;
        alphaSpeed = -alphaSpeed;
    }
}

void ReAppearingText::render() {
    ShaderManager::GetInstance() -> getShader("text") -> use();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", alpha);
    textHandler -> render();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", 1.0f);
}

bool ReAppearingText::isFinished() {
    return false;
}


ReAppearingTextOnlyOnce::ReAppearingTextOnlyOnce(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float & fontSize, const float & fontScale, const glm::vec3 & color) : TextAnimator(content, path, position, size, fontSize, fontScale, color) {
    textHandler = std::make_unique<UITextHandler>(content, path, position, fontScale, fontSize, color);
    alpha = 0.00001f;
    alphaSpeed = 0.5f;
}

ReAppearingTextOnlyOnce::~ReAppearingTextOnlyOnce() {

}

void ReAppearingTextOnlyOnce::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
        alphaSpeed = -alphaSpeed;
    }
    if(alpha <= 0.0f) {
        alpha = 0.0f;
    }
}

void ReAppearingTextOnlyOnce::render() {
    ShaderManager::GetInstance() -> getShader("text") -> use();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", alpha);
    textHandler -> render();
    ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", 1.0f);
}


bool ReAppearingTextOnlyOnce::isFinished() {
    return alpha <= 0.0f;
}


SpriteAnimator::SpriteAnimator(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size) {
    this -> texture = texture;
    this -> position = position;
    this -> size = size;

    float aspect = 1.f / Config::GetInstance() -> GetAspectRatio();
    this -> size.x *= aspect;

    spriteRenderer = SpriteRenderer::getInstance();
    
}

SpriteAnimator::~SpriteAnimator() {

}

AppearSprite::AppearSprite(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size) : SpriteAnimator(texture, position, size) {

}

AppearSprite::~AppearSprite() {

}

void AppearSprite::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
    }
}

void AppearSprite::render() {
    spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("Screen"));
    //spriteRenderer -> DrawSprite(texture, position, size, 0.f, glm::vec3(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), alpha);
    spriteRenderer -> DrawSprite(texture, position, size, 0.f, glm::vec3(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), alpha);
}

bool AppearSprite::isFinished() {
    return alpha >= 1.0f;
}

ReAppearingSprite::ReAppearingSprite(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size) : SpriteAnimator(texture, position, size) {
    alphaSpeed = 0.5f;
    alpha = 0.00001f;
}

ReAppearingSprite::~ReAppearingSprite() {

}

void ReAppearingSprite::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
        alphaSpeed = -alphaSpeed;
    }
    if(alpha <= 0.0f) {
        alpha = 0.0f;
        alphaSpeed = -alphaSpeed;
    }
}

void ReAppearingSprite::render() {
    spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("Screen"));
    spriteRenderer -> DrawSprite(texture, position, size, 0.f, glm::vec3(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), alpha);
}


bool ReAppearingSprite::isFinished() {
    return false;
}

ReAppearingSpriteOnlyOnce::ReAppearingSpriteOnlyOnce(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size) : SpriteAnimator(texture, position, size) {
    alpha = 0.00001f;
    alphaSpeed = 0.5f;
}

ReAppearingSpriteOnlyOnce::~ReAppearingSpriteOnlyOnce() {

}

void ReAppearingSpriteOnlyOnce::update(float deltaTime) {
    alpha += alphaSpeed * deltaTime;
    if(alpha >= 1.0f) {
        alpha = 1.0f;
        alphaSpeed = -alphaSpeed;
    }
    if(alpha <= 0.0f) {
        alpha = 0.0f;
    }
}

void ReAppearingSpriteOnlyOnce::render() {
    spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("Screen"));
    spriteRenderer -> DrawSprite(texture, position, size, 0.f, glm::vec3(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), alpha);
}

bool ReAppearingSpriteOnlyOnce::isFinished() {
    return alpha <= 0.0f;
}




Button :: Button(unsigned int _texture, const glm::vec2 & position, const glm::vec2 & size, const std::string & content, const std::string & path, const float & fontSize, const float & fontScale, const glm::vec3 & color) {
    texture = _texture;
    this -> position = position;
    this -> size = size;
    text = std::make_unique<ReAppearingText>(content, path, position, size, fontSize, fontScale, color);
    
    float aspect = 1.f / Config::GetInstance() -> GetAspectRatio();
    
    this -> size.x *= aspect;

    button = std::make_unique<ReAppearingSprite>(texture, position, this -> size);
    
}

Button::~Button() {

}

void Button::render() {
    button -> render();
    text -> render();
}

bool Button::isHover(const float & xpos, const float & ypos) {
    float x = position.x;
    float y = position.y;
    float width = size.x;
    float height = size.y;

    if(xpos >= x - width /2.f && xpos <= x + width /2.f && ypos  >= y - height / 2.f  && ypos <= y + height /2.f) {
        return true;
    }
    return false;
}

void Button::update(float deltaTime, const float &xpos, const float &ypos) {
    isHovered = isHover(xpos, ypos);
    if(isHovered) {
        float speed = 0.75f;
        button -> setAlphaSpeed(speed);
        text -> setAlphaSpeed(speed);

        button -> update(deltaTime);
        text -> update(deltaTime);

        if(prevHovered == false) {
            SoundManager::GetInstance() -> PlaySound("Hover");
        }

        if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            isClicked = true;
        }

        prevHovered = isHovered;


        return ;
    }
    text -> setAppearant(1.f);
    text -> setAlphaSpeed(0.0f);
    button -> setAlphaSpeed(0.0f);
    button -> setAppearant(0.f);
    text -> update(deltaTime);

    prevHovered = isHovered;
}




