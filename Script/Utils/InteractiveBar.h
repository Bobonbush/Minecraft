#ifndef INTERACTIVEBAR_H
#define INTERACTIVEBAR_H
#include "Texture.h"
#include "Renderer/SpriteRenderer.h"
#include "Texture&Shader/TextureManager.h"
#include "Config.h"


class InteractiveBar {
    private:
        int health;
        int maxHealth = 9;
        SpriteRenderer * spriteRenderer;
        unsigned int texture[2];
        glm::vec2 position = glm::vec2(0.9f, 0.9f);
        glm::vec2 size = glm::vec2(0.05f);
    public:
        
        InteractiveBar(const int maxHealth, const glm::vec2 & position, const glm::vec2 & size, const std::string &full, const std::string &empty);
        ~InteractiveBar();

        void Render();

        void setHealth(int _health);

        int getHealth() const;


        
};

#endif // INTERACTIVEBAR_H