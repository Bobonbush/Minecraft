#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H
#include "StateBase.h"
#include "Player/player.h"
#include "Maths/Ray.h"
#include "Cursor.h"
#include "Chunk/ChunkManager.h"
#include "Renderer/hitbox.h"
#include "Timer.h"
#include "Renderer/AnimationBoxRenderer.h"
#include "Player/HandModel/BlockModel.h"


class PlayingState : Singleton {
    private:
        Player * player;

        static bool pressed[256]; // all the keys are released

        static PlayingState * m_instance;

        Cursor * cursor;
        std::shared_ptr<Item> MouseHoldingItem;
 
        std::vector<DYNAMIC_ENTITY*> entities; 

        std::unique_ptr<AnimationBox> breakingBox;

        std::unique_ptr<HandModel> handModel;
        

        int BlockChoose = -1;

        Timer timer;

        PlayingState();
        HitBox hitBox;

        void MouseProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection);

    public:
        ~PlayingState();
        static PlayingState * GetInstance() {
            if(m_instance == nullptr) {
                m_instance = new PlayingState();
            }
            return m_instance;
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        void EntityProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection);
        void PlayerProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection);
        void ProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 &view, const glm::mat4 & projection, const float &deltaTime);

        

        void FixedProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 &view, const glm::mat4 & projection);
};

#endif // PLAYINGSTATE_H