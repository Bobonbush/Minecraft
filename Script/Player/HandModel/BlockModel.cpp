#include "BlockModel.h"

BlockModel::BlockModel( const glm::vec3 & scale) : HandModel( scale) {
    model = std::make_unique<Model>();
    textureAtlas = std::make_unique<TextureAtlas>("Assets/Default pack.png");

}

BlockModel::~BlockModel() {

}

void BlockModel::addData(const BLOCKID & id) {
    BlockID = (int)id;
    
    if(id == BLOCKID::Hand) {
        //destinationRotation = rotation = glm::vec3(20.f , 10.f, -140.f);
        //defaultRotation = rotation;
        //scale.z *= 2.5f;
        //scale.y *= 2.f;
        scale.x *= 2.5f;
    }
    BlockDataBase * blockDataBase = BlockDataBase::GetInstance();
    auto topCoords = blockDataBase -> getData(id).getBlockData().topCoords;
    auto sideCoords = blockDataBase -> getData(id).getBlockData().sideCoords;
    auto bottomCoords = blockDataBase -> getData(id).getBlockData().bottomCoords;
    
    std::vector<GLfloat> vertices = {
                // Front
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,

                // Top

                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,

                //Bot

                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                
                //Left
                -0.5f, 0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                
                // Right
                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, 0.5f,
                
                // Behind
                -0.5f, 0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f
    };

    auto top = BlockDataBase::GetInstance() -> textureAtlas.getTexture(topCoords);
    auto side = BlockDataBase::GetInstance() -> textureAtlas.getTexture(sideCoords);
    auto bottom = BlockDataBase::GetInstance() -> textureAtlas.getTexture(bottomCoords);
    //SPA::RotateArray2f(side, 2);
    std::vector<GLfloat> texcoords;
    
    texcoords.insert(texcoords.begin(), side.begin(), side.end()); // Front
    
    texcoords.insert(texcoords.end(), top.begin(), top.end()); // Top
    texcoords.insert(texcoords.end(), bottom.begin(), bottom.end()); // Bottom
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Left
    SPA::RotateArray2f(side, 3);
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Right
    SPA::RotateArray2f(side, 1);
    texcoords.insert(texcoords.end(), side.begin(), side.end()); // Behind

    

    for(int i = 0 ; i < 6 * 4 * 2 ; i+= 2) {
       texcoords[i+1] = 1 - texcoords[i+1];
    }
    
    
    std::vector<GLuint> indices = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11,
        12, 13, 15,
        13, 14, 15,
        16, 17, 19,
        17, 18, 19,
        20, 21, 23,
        21, 22, 23
    };


    model -> addData(Mesh(vertices, texcoords, indices));
}

void BlockModel::render(const glm::mat4 & view , const glm::mat4 & projection) {

    //std::cout << actualPosition.x << ' ' << actualPosition.y << ' ' << actualPosition.z << '\n';
    //std::cout << position.x << ' ' << position.y << ' ' << position.z << '\n';
    shader -> use();

    model -> bindVao();
    glActiveTexture(GL_TEXTURE0);
    textureAtlas -> bind();


    glm::mat4 models = glm::mat4(1.0f);
    models = glm::translate(models, position);
    models = glm::rotate(models, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    models = glm::rotate(models, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    models = glm::rotate(models, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    models = glm::scale(models, scale);
    
    
    shader -> setMat4("model", models);
    shader -> setMat4("view", glm::mat4(1.f));
    shader -> setMat4("projection", glm::mat4(1.f));
    shader -> setInt("texture1", 0);

    glDrawElements(GL_TRIANGLES, model -> getIndicesCount(), GL_UNSIGNED_INT, 0);

    //glDisable(GL_DEPTH_TEST);

    glBindVertexArray(0);

}

void BlockModel::update(const float & deltaTime) {
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
        
        if(glm::distance(rotation, destinationRotation) < 5.f) {
            if(!ContinuosHit) {
                rotation = destinationRotation;
                position = destinationPosition;
                Hit = false;
                destinationPosition = defaultPosition;
                destinationRotation = defaultRotation;
            }
        }
    }
}

int BlockModel::getID() {
    return BlockID;
}