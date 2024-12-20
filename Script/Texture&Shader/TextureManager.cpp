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
        int width, height;
        std::tie(width, height) = TextureLoader::GetTextureSize(path);
        textureSize[path] = std::make_pair(width, height);
    }
    return textures[path];
}

std::pair<int ,int > TextureManager::getTextureSize(const char * path) {
    if(textureSize.find(path) == textureSize.end()) {
        textures[path] = TextureLoader::LoadTexture(path);
        int width, height;
        std::tie(width, height) = TextureLoader::GetTextureSize(path);
        textureSize[path] = std::make_pair(width, height);
    }
    return textureSize[path];
}


Mesh TextureManager::get3DMeshFrom2D(const char * path, const float &width , const float &height, const float & depth ) {
    if(meshCache.find(path) == meshCache.end()) {
        meshCache[path] = TextureLoader::extrudeTextureToMesh(path, width, height, depth);
    }
    return meshCache[path];
}