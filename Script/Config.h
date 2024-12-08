#ifndef CONFIG_H
#define CONFIG_H
#include "Texture.h"
#include "Utils/Singleton.h"
#include "File.h"


class Config : public Singleton {
    private : 
        float width = 900;
        float height = 600;
        int antialiasing = 4;
        const int majorVersion = 4;
        const int minorVersion = 6;
        int depthBits = 24;
        int stencilBits = 8;

        GLFWwindow * window;
        static Config * instance;

        bool HidingMouse = false;
        Config() = default;
        

    public :

        
        

        ~Config() {
            delete instance;
            delete window;

        }

        static Config * GetInstance() {
            if(instance == nullptr) {
                instance = new Config();
            }
            return instance;
        }

        // Methods        
        void ChangeConfig();
        
        void ReadConfig();





        // Getter Setter
        

        float GetWidth() const {
            return width;
        }

        float GetHeight() const {
            return height;
        }

        GLFWwindow * GetWindow() const {
            return window;
        }

        float GetAspectRatio() const {
            return width / height;
        }
        void SetVersion();

        bool GetMouseActive() const {
            return HidingMouse;
        }

        void SetMouseActive(bool active) {
            glfwSetInputMode(window, GLFW_CURSOR, !active ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            HidingMouse = active;
        }

        
};

#endif // CONFIG_H