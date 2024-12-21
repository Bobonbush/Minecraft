#include "itemModel.h"

ItemModel::ItemModel( const glm::vec3 & scale, const std::string & path) : HandModel(scale) {
    model = std::make_unique<Model>();
    textureAtlas = std::make_unique<TextureAtlas>("Assets/Items/items.png");
    MineralTexture = std::make_unique<TextureAtlas>("Assets/Items/mineral.png");
    
   
    

}

ItemModel::~ItemModel() {

}

void ItemModel::render(const glm::mat4 &view, const glm::mat4 & projection) {
    
    shader -> use();
    model -> bindVao();
    glActiveTexture(GL_TEXTURE0);

    glDisable(GL_DEPTH_TEST);
    if(Mineral) {
        MineralTexture -> bind();
    }else {
        textureAtlas -> bind();
    }
    shader -> setMat4("view", glm::mat4(1.f));
    shader -> setMat4("projection", glm::mat4(1.f));
    glm::mat4 models = glm::mat4(1.0f);

    models = glm::translate(models, position);
    models = glm::rotate(models, glm::radians( rotation.x), glm::vec3(1.f, 0.f, 0.f));
    models = glm::rotate(models, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    models = glm::rotate(models, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    models = glm::scale(models, scale);
    shader -> setInt("texture1", 0);
    shader -> setMat4("model", models);

    glEnable(GL_DEPTH_TEST);

    glDrawElements(GL_TRIANGLES, model -> getIndicesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void ItemModel::addData(const int & id) {
    itemID = id;
    if(ItemConst::itemMap[id] == ItemConst::Type::Mineral) {
        Mineral = true;
        defaultPosition.x += scale.x * 0.75f;
        defaultPosition.y += scale.y * 0.15f;
        destinationPosition = defaultPosition;
    }else {
        Mineral = false;

        rotation = glm::vec3(0.0f , 50.0f, 30.0f);
        this ->scale.y *= 1.5f;

    //position.y += scale.y;
        defaultPosition.x += scale.x * 0.25f;
        defaultPosition.y += scale.y * 0.15f;
        destinationPosition = defaultPosition;
    

        defaultRotation = rotation;
    
        destinationRotation = rotation;
    }

    TextureManager * textureManager = TextureManager::getInstance();
    ItemDataBase * itemDataBase = ItemDataBase::GetInstance();
    glm::vec2 coords = itemDataBase -> getData(static_cast<ItemID>(id)).getItemData().coords;
    Mesh mesh ;
    if(Mineral) {
        mesh = textureManager ->get3DMeshFrom2DPart(id, "Assets/Items/mineral.png", 32, 32, 0.05f, coords.x,  coords.y);
    }else {
        mesh = textureManager ->get3DMeshFrom2DPart(id, "Assets/Items/items.png", 16, 16, 0.05f, coords.x, coords.y);
    }

    model -> addData(mesh);
}
void ItemModel::update(const float & deltaTime) {

     if(destinationPosition != position) {
        glm::vec3 direction = destinationPosition - position;
        direction = glm::normalize(direction);
        position += direction * movementSpeed * deltaTime;
        if(glm::distance(position, destinationPosition) < 0.1f) {
            if(!ContinuosHit) {
                rotation = destinationRotation;
                position = destinationPosition;
                Hit = false;
                destinationPosition = defaultPosition;
                destinationRotation = defaultRotation;
            }
        }
    }

    if(destinationRotation != rotation) {
        glm::vec3 direction = destinationRotation - rotation;
        direction = glm::normalize(direction);
        rotation += direction * rotationSpeed * deltaTime;
    }
}

int ItemModel::getID() {
    return itemID;
}

void ItemModel::BeingHit() {
    if(ContinuosHit || Hit) {
        return ;
    }

    Hit = true;
    position = destinationPosition;

    rotation = destinationRotation;
    destinationPosition.y += scale.y / 16.f;
    destinationPosition.x -= scale.x / 3.5f;
    destinationRotation = glm::vec3(rotation.x + 40 , rotation.y, rotation.z +  20.f);
}
