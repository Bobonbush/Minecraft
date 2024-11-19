#ifndef CONFIG_H
#define CONFIG_H
#include "Texture.h"
#include "Utils/Singleton.h"
#include "File.h"


class Config : public Singleton {
    private : 
        float width = 1600;
        float height = 1200;
        int antialiasing = 4;
        const int majorVersion = 4;
        const int minorVersion = 6;
        int depthBits = 24;
        int stencilBits = 8;

        GLFWwindow * window;
        static Config * instance;
        Config() = default;
        

    public :

        // Getter Setter
        float GetWidth() const {
            return width;
        }

        float GetHeight() const {
            return height;
        }
        

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

        GLFWwindow * GetWindow() const {
            return window;
        }
        void SetVersion();
        void ChangeConfig();
        
        void ReadConfig();

        
};

#endif // CONFIG_H