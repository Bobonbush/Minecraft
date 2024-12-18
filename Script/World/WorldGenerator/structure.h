#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "Texture.h"
#include "Block/Block.h"
#include "Algorithm.h"


class Structure {
    protected:
        std::vector<std::vector<std::vector<BLOCKID>>> blocks;

        int height;
        int diameter;

        float frequency = 300.f;
        glm::vec3 position;
    public :
        
        Structure() = default;
        Structure(const float& frequency, const glm::vec3& position);
        ~Structure();

        virtual BLOCKID SetBlock(float x, float y , float z) = 0;

        const float getFrequency() const {
            return frequency;
        }
        
};


class PlainTreeStructure : public Structure {

    public:
        PlainTreeStructure(const float & _frequency, const glm::vec3 & position);
        PlainTreeStructure() = default;
        ~PlainTreeStructure();

        BLOCKID SetBlock(float x, float y, float z) override;
};




#endif // STRUCTURE_H