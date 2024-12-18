#ifndef OPTIONMENU_H
#define OPTIONMENU_H
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureManager.h"
#include "States/SceneState.h"
#include "UIUtil.h"
#include "Renderer/SpriteRenderer.h"
#include "States/MenuState.h"


class OptionMenu : public WaitingStage {
    private:
        std::unique_ptr<TextAnimator> TitleName;
        std::unique_ptr<SpriteAnimator> Pickaxe;

        std::vector<std::unique_ptr<Button>> buttons;

        float cooldown = 0.25f;

        MenuState menuState = MenuState::NONE;

    public :
        
        OptionMenu();
        ~OptionMenu();

        void render() override;
        void update(float deltaTime, const float &xpos, const float &ypos) override;
        void FixedUpdate() override;
        void ProcessState() override;

        MenuState getMenuState() {
            return menuState;
        }
};

#endif // OPTIONMENU_H
