#ifndef HANDMODEL_H
#define HANDMODEL_H
#include "Model.h"
#include <iostream>
#include "Texture.h"
#include "Texture&Shader/TextureAtlas.h"

class HandModel {
    private:
        Mesh mesh;
        std::unique_ptr<TextureAtlas> textureAtlas;

    public :
        HandModel(std::string & path);
        ~HandModel();
        void render();
        void update();



        
};


#endif // HANDMODEL_H

