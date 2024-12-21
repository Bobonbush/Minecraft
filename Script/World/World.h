#ifndef WORLD_H
#define WORLD_H
#include "Renderer/RenderMaster.h"
#include "States/SceneState.h"
#include "Application.h"
#include "Chunk/ChunkManager.h"
#include "States/PlayingState.h"
#include "Menu/deathScene.h"
class World : public StateBase {
    private:
        std::unique_ptr<RenderMaster> renderMaster;
        std::unique_ptr<Camera> camera;
        std::vector<ChunkSection> chunks;


        ChunkManager chunkManager;
        glm::mat4 view;
        glm::mat4 projection;
        Player * player;
        PlayingState* playingState;
        Cursor * cursor;
        Config * config;

        std::unique_ptr<StateBase> _next;

        std::unique_ptr<DeathScene> deathScene;

        bool backToMenu = false;


        
    public :
        World();
        virtual ~World() noexcept = default;

        virtual void render() override;

        virtual void Update(float deltaTime, const float &xpos , const float &ypos) override;

        virtual void FixedUpdate(float xpos, float ypos) override;

        std::unique_ptr<StateBase> isNext() override {
            return std::move(_next);
        }

        bool isFinished() override {
            return backToMenu;
        }
        
};

#endif // WORLD_H