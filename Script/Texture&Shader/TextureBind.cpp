#include "TextureBind.h"

TextureBind::TextureBind(const std::string & file) {
    loadFromFile(file);
}

void TextureBind::loadFromFile(const std::string & file) {
    textureID = TextureLoader::LoadTexture((char*)file.c_str());
}

void TextureBind::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

TextureBind::~TextureBind() {
    glDeleteTextures(1, &textureID);
}

