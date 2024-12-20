#include "HandModel.h"


HandModel::HandModel( const glm::vec3 & scale) :  scale(scale) {
    rotation = glm::vec3(-10.f , 50.f, -15.f);
    position = glm::vec3(0.0f);

    Config * config = Config::GetInstance();
    float aspect = 1.f/ config -> GetAspectRatio();
    this -> scale.x *= aspect;

    position.y = -1.2f;
    position.x = 1.f;

    destinationPosition = position;
    destinationPosition.y = -1.0f;
    destinationPosition.y += this -> scale.y / 16.f;
    destinationPosition.x -= this -> scale.x / 1.f;

    destinationRotation = rotation;

    defaultPosition = destinationPosition;

    position.x = destinationPosition.x;
    shader = ShaderManager::GetInstance() -> getShader("tool");

    defaultRotation = rotation;
}

void HandModel::setCooldown(float time) {
    cooldown = time;
}

void HandModel::addData(const Mesh & mesh) {
    model -> addData(mesh);
}

void HandModel::addData(const BLOCKID & id) {
    return ;
}

void HandModel::BeingHit() {
    if(ContinuosHit || Hit) {
        return ;
    }
    Hit = true;
    position = destinationPosition;
    destinationPosition.y += scale.y / 2.f;
    destinationPosition.x -= scale.x / 1.15f;

    destinationRotation = glm::vec3(rotation.x + 80.f, rotation.y - 20.f, rotation.z + 20.f);

    
}


void HandModel::StopContinuosHit() {
    ContinuosHit = false;
}

void HandModel::BeingContinuosHit() {
    if(!ContinuosHit) {
        //StopContinuosHit();
        BeingHit();
        return ;
    }
    ContinuosHit = true;
}
