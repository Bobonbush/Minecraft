#include "itemData.h"


ItemData::ItemData(const std::string &fileName) {
    File * file = File::GetInstance();
    file -> SetJson("Assets/item.json");
    file -> SetNextJson(fileName);
    itemData.coords = glm::vec2(file -> GetJsonFloat("x"), file -> GetJsonFloat("y"));
    file -> PopJson();
}

const ItemDataHolder & ItemData::getItemData() const {
    return itemData;
}