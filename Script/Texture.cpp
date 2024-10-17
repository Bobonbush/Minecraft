#include "Texture.h"


TextureLoader::TextureLoader(){
}

TextureLoader::~TextureLoader(){
}

std::string TextureLoader::prefix[2] = {"png", "jpg"}; // Add more file formats here

unsigned int TextureLoader :: LoadTexturePNG(char* path){
        stbi_set_flip_vertically_on_load(true);
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        //glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        
        // set texture filtering parameters
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        return texture;
}

std::pair<int ,int> TextureLoader::GetTextureSize(char* path){
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    return std::make_pair(width, height);
}


unsigned int TextureLoader::LoadTextureJPG(char* path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        
        unsigned int texture;
        glGenTextures(1, &texture);

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D ,texture);
         
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        
        float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        
        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        if(!data)
        {
            std::cout << "Failed to load texture" << std::endl;
            return -1;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        return texture;



}

unsigned int TextureLoader::LoadTexture(char* path){
        std::string pathstr = path;
        std::string ext = pathstr.substr(pathstr.find_last_of(".") + 1);
        if(ext == prefix[0]){
            return LoadTexturePNG(path);
        }
        else if(ext == prefix[1]){
            return LoadTextureJPG(path);
        }
        else{
            std::cout << "Invalid file format" << std::endl;
            return 0;
        }
}

void TextureLoader::buildCircle(float radius, int vCount , std::vector<glm::vec3>& vertices, std::vector<unsigned int> &indices)
{
    float angle = 360.0f / vCount;

    int triangleCount = vCount - 2;

    std::vector<glm::vec3> temp;
    // positions
    for (int i = 0; i < vCount; i++)
    {
        float currentAngle = angle * i;
        float x = radius * cos(glm::radians(currentAngle));
        float y = radius * sin(glm::radians(currentAngle));
        float z = 0.0f;

        vertices.push_back(glm::vec3(x, y, z));
    }

    // push indexes of each triangle points
    for (int i = 0; i < triangleCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
}



GLFWcursor* TextureLoader::createCustomCursor(const char* imagePath) {
    stbi_set_flip_vertically_on_load(false); // Flip the image vertically
    
    int width, height, channels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load cursor image: " << imagePath << std::endl;
        return nullptr;
    }

    GLFWimage cursorImage;
    cursorImage.width = width;
    cursorImage.height = height;
    cursorImage.pixels = data;

    GLFWcursor* cursor = glfwCreateCursor(&cursorImage, 0, 0);
    stbi_image_free(data);

    return cursor;
}



// SpriteRenderer

SpriteRenderer::SpriteRenderer(Shader shader) : shader(shader) {
    this->initRenderData(0);

}


SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteBuffers(1, &quadEBO);
}


void SpriteRenderer::initRenderData(int pivot) {
    /*
    pivot = 0 : Bottom left
    pivot = 1 : Bottom right
    pivot = 2 : Top left
    pivot = 3 : Top right
    pivot = 4 : Center

    */
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 
    
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void SpriteRenderer::DrawSprite(unsigned int texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.setMat4("model", model);
    shader.setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

 

