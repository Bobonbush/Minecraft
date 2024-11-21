#ifndef SCENESTATE_H
#define SCENESTATE_H
#include "StateBase.h"
#include <stack>

class SceneState {
    private: 

        std::stack<std::unique_ptr<StateBase>> states;
        
    public:
        SceneState() = default;
        virtual ~SceneState() noexcept = default;

        void render();

        void Update(float deltaTime);

        void FixedUpdate(float xpos, float ypos);

        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        
};

#endif // SCENESTATE_H