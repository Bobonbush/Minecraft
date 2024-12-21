#ifndef BLOCKMODEL_H
#define BLOCKMODEL_H
#include "HandModel.h"
#include "Algorithm.h"

class BlockModel : public HandModel {
    private:

        int BlockID;
        std::unique_ptr<TextureAtlas> textureAtlas;
    public:
        BlockModel(const glm::vec3 & scale);
        ~BlockModel();
        void render(const glm::mat4 & view , const glm::mat4 & projection) override;
        void update(const float & deltaTime) override;
        void addData( const int & id) override;

        virtual int getID() override;
        
};

#endif // BLOCKMODEL_H