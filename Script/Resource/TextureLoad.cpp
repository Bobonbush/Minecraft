#include "TextureLoad.h"

TextureManager * TextureManager::instance = nullptr;

TextureManager::TextureManager() {
    
}

TextureManager::~TextureManager() {
    for (auto texture : textures) {
        glDeleteTextures(1, &texture.second);
    }
    delete instance;
}


unsigned int TextureManager::LoadTexture(char * path) {
    if (textures.find(path) != textures.end()) {
        return textures[path];
    }

    textures[path]  = TextureLoader::LoadTexture(path);
    return textures[path];
}

glm::vec2 TextureManager::GetTextureSize(char* path) {
    int width, height;
    if(textures.find(path) == textures.end()) {
        textures[path] = TextureLoader::LoadTexture(path);
    }
    glBindTexture(GL_TEXTURE_2D, textures[path]);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    return glm::vec2(width, height);
}



