#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include "TextureBind.h"
class TextureAtlas : public TextureBind {
    private:
        int imageSize;
        int individualTextureSize;
    
    public:
        TextureAtlas(const std::string &path);
        std::vector<GLfloat> getTexture(const glm::vec2& coords);
};

#endif // TEXTUREATLAS_H