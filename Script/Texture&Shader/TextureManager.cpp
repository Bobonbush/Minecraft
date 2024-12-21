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


Mesh TextureManager::get3DMeshFrom2DPart(const int & id , const char * path, const float & width, const float & height, const float & depth, const float & currentX, const float & currentY) {
    if(meshCache.find(id) == meshCache.end()) {
        
        meshCache[id] = TextureLoader::extrudePartTextureToMesh(path, width, height, currentX, currentY, depth);
    }
    return meshCache[id];
}