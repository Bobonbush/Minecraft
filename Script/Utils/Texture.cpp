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
        stbi_set_flip_vertically_on_load(true);
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

unsigned int TextureLoader::LoadCubeMap(std::vector<std::string> faces){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
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


CubeSurface::CubeSurface(std::shared_ptr<Shader> shader, int face, unsigned int texture) : shader(shader) , texture(texture) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &instanceVBO);
    std::vector<float> vertex;

    if(face == 4 ) {
        vertex = {
            // positions          color             coords        Normals
        0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,      0.0f, 0.0f, 1.0f,  // top right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     0.0f, 0.0f ,1.0f,// bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     0.0f, 0.0f ,1.0f,// bottom left
        -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,     0.0f, 0.0f ,1.0f  // top left 
        };
    }else if(face == 0) {
        vertex = {
            // positions          color             coords         Normals
            -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f, 1.0f, 0.0f,    // top left
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
             0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
            0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   0.0f , 1.0f , 0.0f // top right
           
            
            
        };
    }else if(face == 1) {
        vertex = {
            0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f, // top right
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  0.0f, -1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom left
            -0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f, -1.0f, 0.0f  // top left
        };
    }else if(face == 2) {
        vertex = {
            -0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, // top right
            -0.5f,  -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  -1.0, 0.0f, 0.0f  // top left
        };
    }else if(face == 3) {
        
        vertex = {
             0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  1.0, 0.0f, 0.0f, // top right
             0.5f, 0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  1.0, 0.0f, 0.0f,  // top left
             0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  1.0, 0.0f, 0.0f, // bottom left
            0.5f,  -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  1.0, 0.0f, 0.0f // bottom right
        };
    }else if(face == 5) {
        vertex = {
            -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f, // top right
            -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  0.0f, 0.0f, -1.0f,// bottom right
             0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  0.0f, 0.0f, -1.0f,// bottom left
             0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f  // top left
        };
    }

    float vertices[] = {
        vertex[0], vertex[1], vertex[2] , vertex[3], vertex[4], vertex[5] , vertex[6] , vertex[7] , vertex[8], vertex[9], vertex[10],
        vertex[11], vertex[12], vertex[13] , vertex[14], vertex[15], vertex[16] , vertex[17] , vertex[18] , vertex[19], vertex[20], vertex[21],
        vertex[22], vertex[23], vertex[24] , vertex[25], vertex[26], vertex[27] , vertex[28] , vertex[29] , vertex[30], vertex[31], vertex[32],
        vertex[33], vertex[34], vertex[35] , vertex[36], vertex[37], vertex[38] , vertex[39] , vertex[40] , vertex[41], vertex[42], vertex[43]
    };

    unsigned int indices[] = {
        3, 1, 0, // first triangle
        3, 2, 1  // second triangle
    };

    for(int i = 0 ; i < (int) 1e5 ; i++ ) {
        instancePositions.push_back(glm::vec3(0.0f));
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(2);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (8 * sizeof(float)));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, (int)instancePositions.size() * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1); 

    
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, (int)instancePositions.size() * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
        
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
    
}

CubeSurface::~CubeSurface() {
}

void CubeSurface::Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3> & validPositions) {
    if(validPositions.size() == 0) {
        return;
    }

    
    shader -> use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    shader -> setMat4("model", model);
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    bool diff = false;
    bool neww = false;


    for(int i = 0; i < (int) validPositions.size(); i++) {
        if(i == (int) instancePositions.size()) {
            
            instancePositions.push_back(validPositions[i]);
            neww = true;
            std::cout << "WTF" <<'\n';
            continue;
        }
        if(validPositions[i] != instancePositions[i]) {
            instancePositions[i] = validPositions[i];
            diff = true;
            
            
        }
        instancePositions[i] = validPositions[i];
    }

    
    if(neww) {
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, (int)instancePositions.size() * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if(diff) {
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        int number = (int)validPositions.size();
        glBufferSubData(GL_ARRAY_BUFFER, 0, number * sizeof(glm::vec3), instancePositions.data());
        //glBufferData(GL_ARRAY_BUFFER, number * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instancePositions.size());

    glBindVertexArray(0);
}


void CubeSurface::Render(glm::vec3 position, glm::vec3 scale, glm::mat4 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3> & validPositions) {
    if(validPositions.size() == 0 || Blocked) {
        return;
    }
    shader -> use();
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::scale(model, scale);
    model = model * rotation;
    
    shader -> setMat4("model", model);
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    bool diff = false;
    bool neww = false;


    for(int i = 0; i < (int) validPositions.size(); i++) {
        if(i == (int) instancePositions.size()) {
            
            instancePositions.push_back(validPositions[i]);
            neww = true;
            continue;
        }
        if(validPositions[i] != instancePositions[i]) {
            instancePositions[i] = validPositions[i];
            diff = true;
            
        }
        instancePositions[i] = validPositions[i];
    }

    
    if(neww) {
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, (int)instancePositions.size() * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if(diff) {
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        int number = (int)validPositions.size();
        number = (int) instancePositions.size();
        
        glBufferData(GL_ARRAY_BUFFER, number * sizeof(glm::vec3), instancePositions.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instancePositions.size());

    glBindVertexArray(0);
}

void CubeSurface::SetBlocked(bool value) {
    Blocked = value;
}

CubeBuilder::CubeBuilder(std::shared_ptr<Shader> shader) : shader(shader) {

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


CubeRenderer::CubeRenderer(std::shared_ptr<Shader> shader) : shader(shader) {

}

void CubeRenderer:: LoadCube(unsigned int texture) {
    numBlocks++;
    if(numBlocks > 1) {
        //std::cout << "Only one block can be loaded at a time" << std::endl;
        return;
    }
    CubeBuilder builder(shader);
    builder.BuildSurfaceTop(texture);
    builder.BuildSurfaceBottom(texture);
    builder.BuildSurfaceLeft(texture);
    builder.BuildSurfaceRight(texture);
    builder.BuildSurfaceFront(texture);
    builder.BuildSurfaceBack(texture);

    /*
    face 0 = top
    face 1 = Bot
    face 2 = left
    face 3 = right
    face 4 = front
    face 5 = back
    */

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


void CubeRenderer::Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPosition) {
    for (int i = 0; i < (int) cubeSurfaces.size(); i++) {
        cubeSurfaces[i].Render(position, scale, rotation, view, projection, validPosition);
    }
}

void CubeRenderer::Render(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPosition , std::vector<int> & banFace) {
    int totalRenderer = 0;
    for (int i = 0; i < (int) cubeSurfaces.size(); i++) {
        std::vector<glm::vec3> realValidPosition;
        for(int j = 0 ; j <= (int)banFace.size()-1 ; j++) {
            int mask = (banFace[j] & (1 << i));
            if(mask) {
                continue;
            }
            totalRenderer++;
            realValidPosition.push_back(validPosition[j]);
        }
        cubeSurfaces[i].Render(position, scale, rotation, view, projection, realValidPosition);
    }
}

void CubeRenderer::Render(glm::vec3 position, glm::vec3 scale, glm::mat4 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPosition) {
    for (int i = 0; i < (int) cubeSurfaces.size(); i++) {
        cubeSurfaces[i].Render(position, scale, rotation, view, projection, validPosition);
    }
}

void CubeRenderer::Render(glm::vec3 position, glm::vec3 scale, glm::mat4 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3>& validPosition , std::vector<int> & banFace) {
    for (int i = 0; i < (int) cubeSurfaces.size(); i++) {
        std::vector<glm::vec3> realValidPosition;
        for(int j = 0 ; j <= (int)banFace.size()-1 ; j++) {
            int mask = (banFace[j] & (1 << i));
            if(mask) {
                continue;
            }
            realValidPosition.push_back(validPosition[j]);
        }
        cubeSurfaces[i].Render(position, scale, rotation, view, projection, realValidPosition);
    }
}


void CubeRenderer::SetBlockedSurface(int face, bool value) {
    cubeSurfaces[face].SetBlocked(value);
}

void CubeRenderer::SetFreeSurface() {
    for(int i = 0; i < (int) cubeSurfaces.size(); i++) {
        cubeSurfaces[i].SetBlocked(false);
    }
}


