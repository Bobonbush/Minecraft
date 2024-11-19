#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H
#include "StateBase.h"

class PlayingState : public StateBase {
    public:
        PlayingState();

        void render(std::unique_ptr<RenderMaster>& rendererMaster) override;
        void Update(float deltaTime) override;
};

#endif // PLAYINGSTATE_H
