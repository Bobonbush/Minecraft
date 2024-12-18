#ifndef SCENESTATE_H
#define SCENESTATE_H
#include "StateBase.h"
#include <stack>

class SceneState {
    private: 

        std::stack<std::unique_ptr<StateBase>> states;

        float changeBetweenState = 0.0f;
        float changeBetweenStateMax = 0.5f;
        
    public:
        SceneState() = default;
        virtual ~SceneState() noexcept = default;

        void render();

        void Update(float deltaTime, const float &xpos, const float &ypos);

        void FixedUpdate(float xpos, float ypos);

        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        
};

#endif // SCENESTATE_H