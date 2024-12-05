#include "TextureManager.h"

TextureManager * TextureManager::instance = nullptr;

TextureManager::TextureManager() {
    // Empty
}

TextureManager::~TextureManager() {
    textures.clear();
}

GLuint TextureManager::getTexture(const char * path) {
    if(textures.find(path) == textures.end()) {
        textures[path] = TextureLoader::LoadTexture(path);
    }
    return textures[path];
}

