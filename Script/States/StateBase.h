#ifndef STATEBASE_H
#define STATEBASE_H
#include "Renderer/RenderMaster.h"

class StateBase {
    private:
    public :
        StateBase() {
        }
        virtual ~StateBase() noexcept = default;

        virtual void render(std::unique_ptr<RenderMaster>& rendererMaster) = 0;

        virtual void Update(float deltaTime) = 0;
};

#endif // STATEBASE_H