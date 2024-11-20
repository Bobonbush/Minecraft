#include "BlockData.h"

BlockData::BlockData(const std::string & name) {
    File * file = File::GetInstance();
    file -> SetJson("Assets/BlockData/block.json");
    file -> SetNextJson(name);
    blockData.topCoords = glm::vec2(file -> GetJsonFloat("topX"), file -> GetJsonFloat("topY"));
    blockData.sideCoords = glm::vec2(file -> GetJsonFloat("sideX"), file -> GetJsonFloat("sideY"));
    blockData.bottomCoords = glm::vec2(file -> GetJsonFloat("bottomX"), file -> GetJsonFloat("bottomY"));

}

const BlockDataHolder & BlockData::getBlockData() const {
    return blockData;
}