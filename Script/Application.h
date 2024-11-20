#ifndef APPLICATION_H
#define APPLICATION_H
#include <Texture.h>
#include <memory>
#include "Utils/Singleton.h"
#include "Utils/Camera.h"
#include "Config.h"
#include "Renderer/RenderMaster.h"
#include "States/PlayingState.h"



class Application : public Singleton {
    private:
        float totalTime;
        float lastTime = 0;
        
        float elapsedTime;
        float accumulator = 0.0f;
        float maxFrameTime = 1/ 60.f;
        float Alpha = 1.0f;
        static Application* instance;
        Config * config;
        std::unique_ptr<RenderMaster> renderMaster;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<PlayingState> state;
        ChunkSection chunk;
        //StatePlaying state;

        float lastX = -192313.0f;
        float lastY = -192313.0f;
        void Init();

        void Update();
        void Render(const glm::mat4 & view, const glm::mat4 & projection);

        void FixedUpdate(float xpos, float ypos);
        Application();
        ~Application();
    public:
        static Application * GetInstance() {
            if(instance == nullptr) {
                instance = new Application();
            }
            return instance;
        }
        
        
        
        void Run();
};

#endif // APPLICATION_H