#ifndef MENU_H
#define MENU_H
#include "Texture.h"
#include "mainScreen.h"
#include "States/SceneState.h"
#include "World/World.h"
#include "deathScene.h"



class Menu : public StateBase {
    private:
        std::unique_ptr<WaitingStage> Screen;
        std::vector<std::unique_ptr<StateBase>> nextState;
        std::unique_ptr<StateBase> _next;

        
    
    public :

        

        Menu();
        virtual ~Menu() noexcept = default;

        virtual void render() override;

        virtual void Update(float deltaTime, const float &xpos, const float &ypos) override;

        virtual void FixedUpdate(float xpos, float ypos) override;

        std::unique_ptr<StateBase> isNext() override {
            return std::move(_next);
        }

        



};

#endif // MENU_H