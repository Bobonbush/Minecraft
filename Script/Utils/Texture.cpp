#include "Texture.h"


TextureLoader::TextureLoader(){
}

TextureLoader::~TextureLoader(){
}

std::string TextureLoader::prefix[2] = {"png", "jpg"}; // Add more file formats here

unsigned int TextureLoader :: LoadTexturePNG(const char* path){
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

std::pair<int ,int> TextureLoader::GetTextureSize(const char* path){
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    return std::make_pair(width, height);
}


unsigned int TextureLoader::LoadTextureJPG(const char* path)
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

unsigned int TextureLoader::LoadTexture(const char* path){
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

Mesh TextureLoader::extrudeTextureToMesh(const char* path , int width, int height, float depth) {
    Mesh mesh;

    unsigned char* textureData = stbi_load(path, &width, &height, nullptr, STBI_rgb_alpha);
    
    if(textureData == nullptr) {
        return mesh;
    }
    // Step 1: Create vertices for the front and back faces
    for (int y = 0; y <= height; ++y) {
        for (int x = 0; x <= width; ++x) {
            // Front face

            float realX = static_cast<GLfloat>(x) / width - 0.5f;
            float realY = static_cast<GLfloat>(y) / height - 0.5f;
            

            // Back face

            mesh.vertexPosition.push_back(static_cast<GLfloat>(realX));
            mesh.vertexPosition.push_back(static_cast<GLfloat>(realY));
            mesh.vertexPosition.push_back(depth/2.f);

            mesh.vertexPosition.push_back(static_cast<GLfloat>(realX));
            mesh.vertexPosition.push_back(static_cast<GLfloat>(realY));
            mesh.vertexPosition.push_back(-depth/2.f);

            

            //x += width/2;
            //y += height/2;

            mesh.textureCoords.push_back(static_cast<GLfloat>(x) / width);
            mesh.textureCoords.push_back( static_cast<GLfloat>(y) / height);

            mesh.textureCoords.push_back( static_cast<GLfloat>(x) / width);
            mesh.textureCoords.push_back( static_cast<GLfloat>(y) / height);
            //std::cout << mesh.textureCoords[(int)mesh.textureCoords.size()-2]<< " " << mesh.textureCoords[(int)mesh.textureCoords.size()-1] << std::endl;
            //x -= width/2;
           //y -= height/2;
        }
    }

    // Lambda function to get vertex index in grid (front face and back face alternate)

    

    
    // Step 2: Create faces for edges
    /*
    auto getVertexIndex = [width](int x, int y, bool back) {
        return (y * (width + 1) + x) * 3 + (back ? 1 : 0) * 3;
    };
    */
    

    // Step 2: Create faces for edges

    auto getVertexIndex = [width](int x, int y, bool back) {
        return (y * (width + 1) + x) * 2 + (back ? 1 : 0);
    };
    

    // Step 2: Create faces for edges
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 4; // Assuming 4 bytes per texel (RGBA)
            unsigned char alpha = textureData[index + 3];

            if (alpha == 0) continue; // Skip transparent texels

            // Front face quad
            GLuint v0 = getVertexIndex(x, y, false);
            GLuint v1 = getVertexIndex(x + 1, y, false);
            GLuint v2 = getVertexIndex(x + 1, y + 1, false);
            GLuint v3 = getVertexIndex(x, y + 1, false);

            mesh.indices.push_back(v0);
            mesh.indices.push_back(v1);
            mesh.indices.push_back(v2);
            mesh.indices.push_back(v2);
            mesh.indices.push_back(v3);
            mesh.indices.push_back(v0);

            // Back face quad
            GLuint bv0 = getVertexIndex(x, y, true);
            GLuint bv1 = getVertexIndex(x, y + 1, true);
            GLuint bv2 = getVertexIndex(x + 1, y + 1, true);
            GLuint bv3 = getVertexIndex(x + 1, y, true);

            mesh.indices.push_back(bv0);
            mesh.indices.push_back(bv1);
            mesh.indices.push_back(bv2);
            mesh.indices.push_back(bv2);
            mesh.indices.push_back(bv3);
            mesh.indices.push_back(bv0);

            

            // Horizontal edges
            if (x == 0 || textureData[index - 4 + 3] == 0) {
                // Left face
                GLuint lv0 = getVertexIndex(x, y, false);
                GLuint lv1 = getVertexIndex(x, y + 1, false);
                GLuint lv2 = getVertexIndex(x, y + 1, true);
                GLuint lv3 = getVertexIndex(x, y, true);

                mesh.indices.push_back(lv0);
                mesh.indices.push_back(lv1);
                mesh.indices.push_back(lv2);
                mesh.indices.push_back(lv2);
                mesh.indices.push_back(lv3);
                mesh.indices.push_back(lv0);
            }


            if (x == width - 1 || textureData[index + 4 + 3] == 0) {
                // Right face
                GLuint rv0 = getVertexIndex(x + 1, y, false);
                GLuint rv1 = getVertexIndex(x + 1, y, true);
                GLuint rv2 = getVertexIndex(x + 1, y + 1, true);
                GLuint rv3 = getVertexIndex(x + 1, y + 1, false);

                mesh.indices.push_back(rv0);
                mesh.indices.push_back(rv1);
                mesh.indices.push_back(rv2);
                mesh.indices.push_back(rv2);
                mesh.indices.push_back(rv3);
                mesh.indices.push_back(rv0);
            }

            // Vertical edges
            if (y == 0 || textureData[index - width * 4 + 3] == 0) {
                // Bottom face
                GLuint bv0 = getVertexIndex(x, y, false);
                GLuint bv1 = getVertexIndex(x, y, true);
                GLuint bv2 = getVertexIndex(x + 1, y, true);
                GLuint bv3 = getVertexIndex(x + 1, y, false);

                mesh.indices.push_back(bv0);
                mesh.indices.push_back(bv1);
                mesh.indices.push_back(bv2);
                mesh.indices.push_back(bv2);
                mesh.indices.push_back(bv3);
                mesh.indices.push_back(bv0);
            }

            if (y == height - 1 || textureData[index + width * 4 + 3] == 0) {
                // Top face
                GLuint tv0 = getVertexIndex(x, y + 1, false);
                GLuint tv1 = getVertexIndex(x + 1, y + 1, false);
                GLuint tv2 = getVertexIndex(x + 1, y + 1, true);
                GLuint tv3 = getVertexIndex(x, y + 1, true);

                mesh.indices.push_back(tv0);
                mesh.indices.push_back(tv1);
                mesh.indices.push_back(tv2);
                mesh.indices.push_back(tv2);
                mesh.indices.push_back(tv3);
                mesh.indices.push_back(tv0);
            }
        }
    }

    stbi_image_free(textureData);


    return mesh;
}

TextHandler :: TextHandler(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ShaderManager * shaderManager = ShaderManager::GetInstance();
    shaderManager -> addShader("text", "Shader/textShader.vs", "Shader/textShader.fs");
    shader = shaderManager -> getShader("text");
}

TextHandler::~TextHandler(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TextHandler::LoadFont(const char* font , unsigned int Size) {
    FT_Library ft;
    if(FT_Init_FreeType(&ft)){
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if(FT_New_Face(ft, font, 0, &face)){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, Size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char c = 0; c < 128; c++){
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYPE: Failed to load Glyph ";
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        Characters.insert(std::pair<char, Character>(c, character));   
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextHandler:: RenderMiddleText(std::string text , float x, float y , float scale, glm::vec3 color, float offset, const glm::vec2 & windowSize){
    shader -> use();
    shader -> setVec3("textColor", color);
    shader -> setMat4("projection", glm::mat4(1.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator p;
    float maximum = x;
    float maximum_y = y;

    for(p = text.begin(); p != text.end(); p++ ) {
        Character ch = Characters[*p];
        maximum += ((ch.Advance >> 6) * scale) / windowSize.x + offset;
        float h = ch.Size.y * scale / windowSize.y;
        if(y + h > maximum_y) maximum_y = y + h;
    }

    /*
    if(maximum_y > 1.00f) {
        y -= (maximum_y - 1.00f) /2.f;
    }

    if(maximum > 1.00f) {
        x -= (maximum - 1.00f) /4.f ;
    }
    */

    x -= (maximum - x) / 2;
    y -= (maximum_y - y) / 2;

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end() ; c++) {
        Character ch = Characters[*c];
        float xpos = x + (ch.Bearing.x * scale) / windowSize.x;
        float ypos = y - ((ch.Size.y - ch.Bearing.y) * scale) / windowSize.y + offset;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        w = w / windowSize.x;
        h = h / windowSize.y;

        float vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},        // Top left
            {xpos, ypos, 0.0, 1.0},            // Bottom left
            {xpos + w, ypos, 1.0, 1.0},        // Bottom right

            {xpos, ypos + h, 0.0, 0.0},        // Top left
            {xpos + w, ypos, 1.0, 1.0},        // Bottom right
            {xpos + w, ypos + h, 1.0, 0.0}      // Top right
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += ((ch.Advance >> 6) * scale) / windowSize.x + offset;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}