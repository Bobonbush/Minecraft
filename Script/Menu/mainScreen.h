#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureManager.h"
#include "States/SceneState.h"
#include "UIUtil.h"
#include "Renderer/SpriteRenderer.h"
#include "States/MenuState.h"
#include "optionMenu.h"
#include "Texture&Shader/SoundManager.h"


class MainScreen : public WaitingStage {
    private:
        SpriteRenderer * spriteRenderer;   // Render Sword
        SoundManager * soundManager;
        std::unique_ptr<TextAnimator> TitleName;
        bool LoadedStudioName = false;
        std::unique_ptr<TextAnimator> StudioName;
        std::unique_ptr<TextAnimator> StartGame;
        std::unique_ptr<SpriteAnimator> StudioLogo;
        glm::vec2 Titleposition = glm::vec2(0.0f, 0.0f);
        glm::vec2 TitleSize = glm::vec2(3.75f , 0.35f);

        SoundEngine * soundEngine;

        std::unique_ptr<SpriteAnimator> ClearScreen;

        std::unique_ptr<SpriteAnimator> Pickaxe;

        float afterIntroMaxTime = 2.75f;
        float afterIntroCurrentTime = 0.f;

        unsigned int Pickage;


        
    public :
        
        MainScreen();
        ~MainScreen();


        void render() override;
        void update(float deltaTime, const float &xpos , const float &ypos) override;
        void FixedUpdate() override;
        void ProcessState() override;

};

#endif // MAINSCREEN_H