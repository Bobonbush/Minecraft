#ifndef DEATHSCENE_H
#define DEATHSCENE_H
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureManager.h"
#include "States/SceneState.h"
#include "UIUtil.h"
#include "States/MenuState.h"
#include "Texture&Shader/SoundManager.h"


class DeathScene : public WaitingStage {
    private:
        std::unique_ptr<SpriteAnimator> ClearScreen;
        std::unique_ptr<TextAnimator> TitleName;
        MenuState menuState;
        std::vector<std::unique_ptr<Button>> buttons;
        bool isPlaySong = false;

        void Reset();
    public :
        
        DeathScene();
        ~DeathScene();  

        void render() override;
        void update(float deltaTime, const float &xpos , const float &ypos) override;
        void FixedUpdate() override;
        void ProcessState() override;

        MenuState getMenuState() {
            MenuState temp = menuState;
            menuState = MenuState::NONE;
            return temp;
        }

        


};

#endif // DEATHSCENE_H