#ifndef UIUTIL_H
#define UIUTIL_H
#include "Texture.h"
#include "Texture&Shader/TextureManager.h"
#include "Config.h"
#include "Renderer/SpriteRenderer.h"
#include <iostream>
#include "Texture&Shader/SoundManager.h"




class UITextHandler {
    private:
        unsigned int texture;
        std::unique_ptr<TextHandler> textHandler;
        glm::vec2 position;
        //glm::vec2 size;
        glm::vec3 color;
        std::string content;

        float scale;
        float FontSize ;
    public :
        UITextHandler(const std::string & content ,const std::string & path, const glm::vec2 & position, const float &scale, const float& FontSize , const glm::vec3 & color);
        ~UITextHandler();
        void render();

};


class TextAnimator {
    protected:
        float alpha = 0.0f;
        float alphaSpeed = 0.25f;

        std::unique_ptr<UITextHandler> textHandler;

    public :
        TextAnimator(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float &fontSize, const float &fontScale, const glm::vec3 & color);
        ~TextAnimator();
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual bool isFinished() = 0;

        void setAppearant(float alpha) {
            this -> alpha = alpha;
        }

        void setAlphaSpeed(float alphaSpeed) {
            this -> alphaSpeed = alphaSpeed;
        }
};


class AppearText : public TextAnimator {

    public :
        AppearText(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float &fontSize, const float &fontScale, const glm::vec3 & color);
        ~AppearText();
        void update(float deltaTime) override;
        void render() override;
        bool isFinished() override;
};


class ReAppearingText : public TextAnimator {
    public :
        
        ReAppearingText(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float &fontSize, const float &fontScale, const glm::vec3 & color);
        ~ReAppearingText();
        void update(float deltaTime) override;
        void render() override;

        bool isFinished() override;
        
};


class ReAppearingTextOnlyOnce : public TextAnimator {
    public :
        
        ReAppearingTextOnlyOnce(const std::string & content, const std::string & path, const glm::vec2 & position, const glm::vec2 & size, const float &fontSize, const float &fontScale, const glm::vec3 & color);
        ~ReAppearingTextOnlyOnce();
        void update(float deltaTime) override;
        void render() override;

        bool isFinished() override; 
};



class SpriteAnimator {
    protected:
        float alpha = 0.0f;
        float alphaSpeed = 0.25f;
        SpriteRenderer * spriteRenderer;
        unsigned int texture;
        glm::vec2 position;
        glm::vec2 size;
    public :

        SpriteAnimator(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size);
        ~SpriteAnimator();
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual bool isFinished() = 0;

        void setAppearant(float alpha) {
            this -> alpha = alpha;
        }

        void setAlphaSpeed(float alphaSpeed) {
            this -> alphaSpeed = alphaSpeed;
        }
};

class AppearSprite : public SpriteAnimator {
    public :
        AppearSprite(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size);
        ~AppearSprite();
        void update(float deltaTime) override;
        void render() override;
        bool isFinished() override;
};


class ReAppearingSprite : public SpriteAnimator {
    public :
        ReAppearingSprite(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size);
        ~ReAppearingSprite();
        void update(float deltaTime) override;
        void render() override;
        bool isFinished() override;
};


class ReAppearingSpriteOnlyOnce : public SpriteAnimator {
    public :
        ReAppearingSpriteOnlyOnce(unsigned int texture, const glm::vec2 & position, const glm::vec2 & size);
        ~ReAppearingSpriteOnlyOnce();
        void update(float deltaTime) override;
        void render() override;
        bool isFinished() override;
};



class Button {
    bool isHovered = false;
    bool prevHovered = false;
    bool isClicked = false;
    private:
        std::unique_ptr<ReAppearingSprite> button;
        std::unique_ptr<TextAnimator> text;
        unsigned int texture;
        glm::vec2 position;
        glm::vec2 size;

        bool isHover(const float & xpos, const float & ypos);
    public:

        Button(unsigned int _texture, const glm::vec2 & position, const glm::vec2 & size, const std::string & content, const std::string & path, const float & fontSize, const float & fontScale, const glm::vec3 & color);
        ~Button();

        

        void render() ;
        void update(float deltaTime, const float &xpos, const float &ypos);

        const bool isClickedButton() {
            return isClicked;
        }

};




#endif // UIUTIL_H