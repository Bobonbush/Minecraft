#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include "TextureBind.h"
class TextureAtlas : public TextureBind {
    private:
        std::pair<int,int> imageSize;
        int individualTextureSize;
    
    public:
        TextureAtlas(const std::string &path);
        std::vector<GLfloat> getTexture(const glm::vec2& coords);
        void setIndividualTextureSize(const int & size);

        float getSpaceBetween() const {
            return 1.0f / (float)individualTextureSize;
        }
};

#endif // TEXTUREATLAS_H