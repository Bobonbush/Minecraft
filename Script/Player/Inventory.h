#ifndef INVENTORY_H
#define INVENTORY_H
#include "Texture.h"
#include "Texture&Shader/ShaderManager.h"
#include "Texture&Shader/TextureAtlas.h"
#include "memory.h"


class Inventory {
    public : 
        // Constraints for the inventory
        const static float MAX_SIZE;
        const static int MAX_ROW = 4;
        const static int MAX_COL = 9;
        const static int MAX_BOX = MAX_ROW * MAX_COL;

        const static int handCol = 9;  
        const static int handRow = 1;
        
};

#endif // INVENTORY_H