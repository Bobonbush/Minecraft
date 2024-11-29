#ifndef CURSOR_H
#define CURSOR_H
#include "Texture.h"
#include "Utils/Singleton.h"
#include "Texture&Shader/ShaderManager.h"


class Cursor : public Singleton {
 
    enum CursorState : int {
        CLICK = 0,
        RELEASE,
        HOLD
    };

    enum MOUSE_BUTTONS : int {
        LEFT = 0,
        RIGHT
    };

    

    static Cursor * m_instance;
    private:
        unsigned int VAO, VBO, EBO;
        unsigned int m_texture;
        std::shared_ptr<Shader> m_shader;
        bool pressed[2];
        Cursor();
        
    public :

        enum MOUSE_EVENT : int {
            LEFT_CLICK = 0,
            RIGHT_CLICK,
            LEFT_RELEASE,
            RIGHT_RELEASE,
            LEFT_HOLD,
            RIGHT_HOLD
        };
        static Cursor * GetInstance() {
            if(m_instance == nullptr) {
                m_instance = new Cursor();
            }
            return m_instance;
        }
        ~Cursor();

        void Draw( const float halfX = 0.5f, const float halfY = 0.5f);
        int GetInput();
};

#endif