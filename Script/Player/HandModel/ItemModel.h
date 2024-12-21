#include "HandModel.h"
#include "Texture&Shader/TextureManager.h"
#include "Item/itemDataBase.h"
#include "Item/ItemConst.h"
class ItemModel : public HandModel {
    private:
        std::unique_ptr<TextureAtlas> textureAtlas;
        int itemID;
        std::unique_ptr<TextureAtlas> MineralTexture;

        bool Mineral = false;

    public:
        ItemModel(const glm::vec3 & scale, const std::string & path);
        ~ItemModel();
        void addData(const int & id) override;
        void render(const glm::mat4 &view, const glm::mat4 & projection ) override;
        void update(const float & deltaTime) override;      
        void BeingHit();
        virtual int getID() override;
};