#ifndef TEXTUREBIND_H
#define TEXTUREBIND_H
#include <string>
#include <Texture.h>
class TextureBind {

    private:
        unsigned int textureID;
    public:
        TextureBind() = default;
        TextureBind(const std::string & file);

        ~TextureBind();

        void loadFromFile(const std::string & file );

        void bind() const;

};

#endif // TEXTUREBIND_H