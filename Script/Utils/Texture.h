#ifndef TEXTURE_H
#define TEXTURE_H
#define STBN_IMAGE_IMPLEMENTATION

#include <GLFW/stb_image.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include "ft2build.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture&Shader/ShaderManager.h"
#include FT_FREETYPE_H


#include <map>
#include "shader.h"
#include <memory>
#include <chrono>
#include "Mesh.h"


class TextureLoader {
    
    private:
    static unsigned int LoadTexturePNG(const char* path);
    static unsigned int LoadTextureJPG(const char* path);
    static const unsigned char* LoadTextureChar(char* path);
    static std::string prefix[2];
    


    public:
    TextureLoader();            // Init everything for texture}

    ~TextureLoader();


    static unsigned int LoadTexture(const char* path);
    static std::pair<int ,int> GetTextureSize(const char* path);

    static void buildCircle(float radius, int vCount, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
    static GLFWcursor* createCustomCursor(const char* imagePath);

    static unsigned int LoadCubeMap(std::vector<std::string> faces);

    static Mesh extrudeTextureToMesh(const char* path , int width, int height, float depth);
    
};



class TextHandler {

    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph

    };
    private : 
    std::map<char, Character> Characters;
    std::shared_ptr<Shader> shader;
    unsigned int VAO, VBO;
    
    public:
    TextHandler();
    ~TextHandler();
    void LoadFont(const char* fontPath, unsigned int fontSize);
    void RenderMiddleText( std::string text, float x, float y, float scale, glm::vec3 color, float offset, const glm::vec2 & windowSize);
    
};


#endif