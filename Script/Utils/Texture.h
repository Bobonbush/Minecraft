#ifndef TEXTURE_H
#define TEXTURE_H
#define STBN_IMAGE_IMPLEMENTATION

#include <GLFW/stb_image.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <map>
#include "shader.h"
#include <memory>
#include <chrono>


class TextureLoader {
    
    private:
    static unsigned int LoadTexturePNG(char* path);
    static unsigned int LoadTextureJPG(char* path);
    static std::string prefix[2];
    


    public:
    TextureLoader();            // Init everything for texture}

    ~TextureLoader();


    static unsigned int LoadTexture(char* path);
    static std::pair<int ,int> GetTextureSize(char* path);

    static void buildCircle(float radius, int vCount, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
    static GLFWcursor* createCustomCursor(const char* imagePath);

    static unsigned int LoadCubeMap(std::vector<std::string> faces);
};

#endif