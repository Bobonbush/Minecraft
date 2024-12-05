#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H
#include "StateBase.h"
#include "Player/player.h"
#include "Maths/Ray.h"
#include "Cursor.h"
#include "Chunk/ChunkManager.h"
#include "Renderer/hitbox.h"

class PlayingState : Singleton {
    private:
        Player * player;

        static bool pressed[256]; // all the keys are released

        static PlayingState * m_instance;

        Cursor * cursor;

        std::vector<DYNAMIC_ENTITY*> entities; 

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

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            if(key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
                if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                } else {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
        }

        void EntityProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection);
        void PlayerProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection);
        void ProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 &view, const glm::mat4 & projection);

        

        void FixedProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 &view, const glm::mat4 & projection);
};

#endif // PLAYINGSTATE_H