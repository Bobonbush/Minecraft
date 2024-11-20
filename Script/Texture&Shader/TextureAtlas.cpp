#include "TextureAtlas.h"

TextureAtlas :: TextureAtlas(const std::string &path) {
    loadFromFile(path);
    imageSize = 256;
    individualTextureSize = 16;
}

std::vector<GLfloat> TextureAtlas::getTexture(const glm::vec2 & coords) {
    std::vector<GLfloat> textureCoords;
    float x = coords.x;
    float y = coords.y;

    float xMin = x * individualTextureSize / imageSize;
    float xMax = (x + 1) * individualTextureSize / imageSize;
    float yMin = y * individualTextureSize / imageSize;
    float yMax = (y + 1) * individualTextureSize / imageSize;

    textureCoords.push_back(xMax);
    textureCoords.push_back(yMax);

    textureCoords.push_back(xMax);
    textureCoords.push_back(yMin);

    textureCoords.push_back(xMin);
    textureCoords.push_back(yMin);

    textureCoords.push_back(xMin);
    textureCoords.push_back(yMax);

    return textureCoords;
}