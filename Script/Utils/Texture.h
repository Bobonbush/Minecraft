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
};








class CubeSurface { 
    private:
        unsigned int VAO, VBO, EBO;
        Shader &shader;
        unsigned int texture;
        unsigned int instanceVBO;
        std::vector<glm::vec3> instancePositions;
    public :

        CubeSurface(Shader & shader ,int face, unsigned int texture);
        ~CubeSurface();
        void Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPosition);
        
};


class CubeBuilder {
    private :
        std::vector<CubeSurface> cubeSurfaces;
        Shader &shader;
    public:

        CubeBuilder(Shader &shader);
        ~CubeBuilder();
        void BuildSurfaceTop(unsigned int texture);
        void BuildSurfaceBottom(unsigned int texture);
        void BuildSurfaceLeft(unsigned int texture);
        void BuildSurfaceRight(unsigned int texture);
        void BuildSurfaceFront(unsigned int texture);
        void BuildSurfaceBack(unsigned int  texture);

        std::vector<CubeSurface> GetCube();
};

class CubeRenderer {
    private:
        std::vector<CubeSurface> cubeSurfaces;
        Shader& shader;
        int numBlocks = 0;

    public :

        CubeRenderer(Shader &shader);

        void LoadCube(unsigned int texture);
        void LoadCube(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right, unsigned int front, unsigned int back);
        void LoadCube(unsigned int top , unsigned int overall);
        void LoadCube(unsigned int top , unsigned int around, unsigned int bottom);

        void Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPositions);
};



#endif