#include "HandModel.h"


class ItemModel : public HandModel {
    private:
        std::unique_ptr<TextureAtlas> textureAtlas;
        int itemID;
    public:
        ItemModel(const glm::vec3 & scale, int itemID, const std::string & path);
        ~ItemModel();
        void render(const glm::mat4 &view, const glm::mat4 & projection ) override;
        void update(const float & deltaTime) override;      

        virtual int getID() override;
};