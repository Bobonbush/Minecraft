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


CubeSurface::CubeSurface(Shader &shader, int face, unsigned int texture) : shader(shader) , texture(texture) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    std::vector<float> vertex;

    if(face == 4 ) {
        vertex = {
            // positions          color             coords
        0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
    }else if(face == 0) {
        vertex = {
            // positions          color             coords
            0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
        };
    }else if(face == 1) {
        vertex = {
            0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
        };
    }else if(face == 2) {
        vertex = {
            -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            -0.5f,  -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
        };
    }else if(face == 3) {
        
        vertex = {
            0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f,  -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
        };
    }else if(face == 5) {
        vertex = {
            -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
        };
    }

    float vertices[] = {
        vertex[0], vertex[1], vertex[2], vertex[3], vertex[4], vertex[5], vertex[6], vertex[7],
        vertex[8], vertex[9], vertex[10], vertex[11], vertex[12], vertex[13], vertex[14], vertex[15],
        vertex[16], vertex[17], vertex[18], vertex[19], vertex[20], vertex[21], vertex[22], vertex[23],
        vertex[24], vertex[25], vertex[26], vertex[27], vertex[28], vertex[29], vertex[30], vertex[31]
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
}

CubeSurface::~CubeSurface() {
}

void CubeSurface::Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection) {
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


CubeBuilder::CubeBuilder(Shader &shader) : shader(shader) {

}



CubeBuilder::~CubeBuilder() {

}

void CubeBuilder::BuildSurfaceTop(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 0, texture));
}

void CubeBuilder::BuildSurfaceBottom(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 1, texture));
}

void CubeBuilder::BuildSurfaceLeft(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 2, texture));
}

void CubeBuilder::BuildSurfaceRight(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 3, texture));
}

void CubeBuilder::BuildSurfaceFront(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 4, texture));
}

void CubeBuilder::BuildSurfaceBack(unsigned int texture) {
    cubeSurfaces.push_back(CubeSurface(shader, 5, texture));
}


std::vector<CubeSurface> CubeBuilder::GetCube() {
    return cubeSurfaces;
}


CubeRenderer::CubeRenderer(Shader &shader) : shader(shader) {

}

void CubeRenderer:: LoadCube(unsigned int texture) {
    CubeBuilder builder(shader);
    builder.BuildSurfaceTop(texture);
    builder.BuildSurfaceBottom(texture);
    builder.BuildSurfaceLeft(texture);
    builder.BuildSurfaceRight(texture);
    builder.BuildSurfaceFront(texture);
    builder.BuildSurfaceBack(texture);

    cubeSurfaces = builder.GetCube();
}

void CubeRenderer:: LoadCube(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right, unsigned int front, unsigned int back) {
    CubeBuilder builder(shader);
    builder.BuildSurfaceTop(top);
    builder.BuildSurfaceBottom(bottom);
    builder.BuildSurfaceLeft(left);
    builder.BuildSurfaceRight(right);
    builder.BuildSurfaceFront(front);
    builder.BuildSurfaceBack(back);

    cubeSurfaces = builder.GetCube();
}


void CubeRenderer:: LoadCube(unsigned int top, unsigned int overall) {
    CubeBuilder builder(shader);
    builder.BuildSurfaceTop(top);
    builder.BuildSurfaceBottom(overall);
    builder.BuildSurfaceLeft(overall);
    builder.BuildSurfaceRight(overall);
    builder.BuildSurfaceFront(overall);
    builder.BuildSurfaceBack(overall);

    cubeSurfaces = builder.GetCube();
}


void CubeRenderer:: LoadCube(unsigned int top, unsigned int around, unsigned int bottom) {
    CubeBuilder builder(shader);
    builder.BuildSurfaceTop(top);
    builder.BuildSurfaceBottom(bottom);
    builder.BuildSurfaceLeft(around);
    builder.BuildSurfaceRight(around);
    builder.BuildSurfaceFront(around);
    builder.BuildSurfaceBack(around);

    cubeSurfaces = builder.GetCube();
}


void CubeRenderer::Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection) {
    for (int i = 0; i < (int) cubeSurfaces.size(); i++) {
        cubeSurfaces[i].Render(position, scale, rotation, view, projection);
    }
}

