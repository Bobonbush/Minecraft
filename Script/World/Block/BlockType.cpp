#include "BlockType.h"


BlockType::BlockType(const std::string & fileName) : data(fileName) {}

const BlockData& BlockType::getData() const {
    return data;
}