#include "TextureAtlas.h"

TextureAtlas :: TextureAtlas(const std::string &path) {
    loadFromFile(path);
    imageSize = TextureLoader::GetTextureSize(path.c_str());
    individualTextureSize = 16;
}

std::vector<GLfloat> TextureAtlas::getTexture(const glm::vec2 & coords) {
    std::vector<GLfloat> textureCoords;
    float x = coords.x;
    float y = coords.y;

    float xMin = x * individualTextureSize / imageSize.first;
    float xMax = (x + 1) * individualTextureSize / imageSize.first;
    float yMin = y * individualTextureSize / imageSize.second;
    float yMax = (y + 1) * individualTextureSize / imageSize.second;

    textureCoords.push_back(xMin);
    textureCoords.push_back(yMin);

    textureCoords.push_back(xMin);
    textureCoords.push_back(yMax);

    textureCoords.push_back(xMax);
    textureCoords.push_back(yMax);

    textureCoords.push_back(xMax);
    textureCoords.push_back(yMin);

    

    

    return textureCoords;
}

void TextureAtlas::setIndividualTextureSize(const int & size) {
    individualTextureSize = size;
}