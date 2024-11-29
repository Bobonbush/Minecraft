#ifndef WORLD_H
#define WORLD_H
#include "Renderer/RenderMaster.h"
#include "States/SceneState.h"
#include "Application.h"
#include "Chunk/ChunkManager.h"
#include "States/PlayingState.h"
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


        
    public :
        World();
        virtual ~World() noexcept = default;

        virtual void render() override;

        virtual void Update(float deltaTime) override;

        virtual void FixedUpdate(float xpos, float ypos) override;
        
};

#endif // WORLD_H