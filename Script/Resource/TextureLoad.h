#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Texture.h"
#include <map>
#include "Algorithm.h"


class TextureManager {
    private:
        static TextureManager * instance;
        std::map<std::string, unsigned int> textures;
        TextureManager();
    public:
        ~TextureManager();
        
        unsigned int LoadTexture(char* path);

        static TextureManager* getInstance() {
            if (instance == nullptr) {
                instance = new TextureManager();
            }
            return instance;
        }

        glm::vec2 GetTextureSize(char* path);


};

#endif