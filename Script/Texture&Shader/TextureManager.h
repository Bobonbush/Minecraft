#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
#include "Utils/Singleton.h"
class TextureManager : public Singleton {   // Proxy x Singleton
    private:
    std::map<std::string, GLuint> textures;
    std::map<std::string, std::pair<int, int>> textureSize;
    std::map<int, Mesh> meshCache;
    static TextureManager * instance;
    TextureManager();
    public:
    static TextureManager * getInstance() {
        if(instance == nullptr) {
            instance = new TextureManager();
        }
        return instance;
    }
    
    ~TextureManager();
    GLuint getTexture(const char * path);
    std::pair<int ,int > getTextureSize(const char * path);
   Mesh get3DMeshFrom2DPart(const int & id, const char * path, const float & width, const float & height, const float & depth, const float & currentX, const float & currentY);
};

#endif