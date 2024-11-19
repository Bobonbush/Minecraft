#include <Texture.h>
#include <memory>
class Application {
    private:
        GLFWwindow * window;
        float totalTime;
        float lastTime = 0;
        
        float elapsedTime;
        float accumulator = 0.0f;
        float maxFrameTime = 1/ 60.f;
        float Alpha = 1.0f;

        void Init();

        void Update();
        void Render();

        void FixedUpdate(float xpos, float ypos);

    public:
        Application();
        ~Application();
        void Run();
};