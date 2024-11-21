#ifndef STATEBASE_H
#define STATEBASE_H
#include "Renderer/RenderMaster.h"

class StateBase {
    private:
    public :
        StateBase() {
        }
        virtual ~StateBase() noexcept = default;

        virtual void render() = 0;
        virtual void Update(float deltaTime) = 0;

        virtual void FixedUpdate(float xpos, float ypos) = 0;
};

#endif // STATEBASE_H