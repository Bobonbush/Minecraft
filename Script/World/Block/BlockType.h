#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H 
#include "BlockData.h"

class BlockType {
    public :
        BlockType(const std::string & fileName);
        virtual ~BlockType() = default;

        const BlockData& getData() const;

    private:
        BlockData data;
};


class DefaultBlock : public BlockType {
    public:
        DefaultBlock(const std::string& fileName) : BlockType(fileName) {};
};

#endif // BLOCKTYPE_H