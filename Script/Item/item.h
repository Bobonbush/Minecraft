#ifndef ITEM_H
#define ITEM_H
#include "Texture.h"

class Item {
    private:
        
    public:
        Item(const std::string &name, const std::string &description, int id, int stackSize, const std::string &texturePath);
        ~Item();
        const std::string &getName() const;
        const std::string &getDescription() const;
        int getID() const;
        int getStackSize() const;
        unsigned int getTexture() const;
};

#endif // ITEM_H