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
        virtual void Update(float deltaTime, const float &xpos , const float &ypos) = 0;

        virtual void FixedUpdate(float xpos, float ypos) = 0;

        virtual std::unique_ptr<StateBase> isNext() = 0;
        virtual bool isFinished() {
            return false;
        }
};

#endif // STATEBASE_H