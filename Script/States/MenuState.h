#ifndef WAITINGSTAGE_H
#define WAITINGSTAGE_H

#include <memory>

class WaitingStage {
    private:
        std::unique_ptr<WaitingStage> nextState;
    protected:
        bool _next = false;
    public :

        enum class MenuState {
            NONE,
            PLAY,
            QUIT,
            Respawn
        };
        WaitingStage();
        virtual ~WaitingStage() noexcept = default;
        virtual void render() = 0;
        virtual void update(float deltaTim, const float &xpos, const float &ypos) = 0;
        virtual void FixedUpdate() = 0;
        virtual void ProcessState() = 0;

        virtual MenuState getMenuState() ;

        void setNextState(std::unique_ptr<WaitingStage> nextState) {
            this -> nextState = std::move(nextState);
        }

        std::unique_ptr<WaitingStage>  getNextState() {
            return std::move(nextState);
        }

        const bool isNext() const {
            return _next;
        }
};

#endif // WAITINGSTAGE_H