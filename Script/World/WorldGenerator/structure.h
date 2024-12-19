#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "Texture.h"
#include "Block/Block.h"
#include "Algorithm.h"


class Structure {
    protected:
        std::vector<std::pair<glm::vec3 , BLOCKID>> blocks;

        int height;
        int diameter;

        float frequency = 300.f;
        glm::vec3 position;

        void BuildVerticalStructure(const float &x , const float &z, const float &y, const BLOCKID &block);
        void BuildHorizontalStructure(const float &x , const float &z, const float &y, const BLOCKID &block, const float &dia); 
    
    public :
        
        Structure() = default;
        Structure(const float& frequency, const glm::vec3& position);
        ~Structure();


        const std::vector<std::pair<glm::vec3 , BLOCKID>> & getBlocks() const {
            return blocks;
        }

        
        const float getFrequency() const {
            return frequency;
        }
        
};


class PlainTreeStructure : public Structure {

    public:
        PlainTreeStructure(const float & _frequency, const glm::vec3 & position);
        PlainTreeStructure() = default;
        ~PlainTreeStructure();
};



class CactusStructure : public Structure {
    public:
        CactusStructure(const float & _frequency, const glm::vec3 & position);
        CactusStructure() = default;
        ~CactusStructure();
};


class SpecialTreeStructure : public Structure {
    public:
        SpecialTreeStructure(const float & _frequency, const glm::vec3 & position);
        SpecialTreeStructure() = default;
        ~SpecialTreeStructure();
};



#endif // STRUCTURE_H