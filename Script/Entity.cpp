#include "Entity.h"


void DYNAMIC_ENTITY::addForce(const glm::vec3 &force) {
    this -> force += force;
}

void DYNAMIC_ENTITY::ApplyGravity() {
    addForce(glm::vec3(0.0f, -PhysicConst::GRAVITY * mass , 0.f));
}

void DYNAMIC_ENTITY::update(float deltaTime) {
}

void DYNAMIC_ENTITY::FixedUpdate() {
    if(!isFlying) {
        ApplyGravity();
    }
    oldWalking = Walking;
    
    isGrounded = false;
    applyForce();
    velocity += acceleration;
    resolveCollision();
    
    
    velocity.x *= friction;
    velocity.z *= friction;

    if(SPA::abs(velocity.x) < 0.001f ) {
        velocity.x = 0;
    }

    if(SPA::abs(velocity.z) < 0.001f ) {
        velocity.z = 0;
    }



    if(UnderWater) {
        velocity.y *= friction*1.15f;
    }

    

    
    

    if(isFlying) {
        velocity.y *= friction;
    }
    acceleration = glm::vec3(0.0f);
}

void DYNAMIC_ENTITY::addCollisioner(const std::vector<AABB> & boxe) {
    nearBoxes = boxe;
}

void DYNAMIC_ENTITY::resolveCollision() {
    position.y += velocity.y;
    box.update(position);
    
    for(AABB & boxe : nearBoxes) {
        if(!getColliding(boxe)) {
            continue;
        }

        glm::vec3 minBox =  boxe.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox =  boxe.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 minBox2 = box.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox2 = box.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 overlap = glm::vec3(0.0f);

        if(velocity.y < 0) {
            overlap.y = maxBox.y - minBox2.y;
        } else {
            overlap.y = minBox.y - maxBox2.y;
        }
        
        
    

        position.y += overlap.y;
        box.update(position);
    
        
        
        velocity.y = 0;
        isGrounded = true;
        break;
    }


    position.x += velocity.x;
    
    box.update(position);
    
    for(AABB & boxe : nearBoxes) {
        if(!getColliding(boxe)) {
            continue;
        }

        glm::vec3 minBox =  boxe.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox =  boxe.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 minBox2 = box.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox2 = box.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 overlap = glm::vec3(0.0f);

        if(velocity.x < 0) {
            overlap.x = maxBox.x - minBox2.x;
        } else {
            overlap.x = minBox.x - maxBox2.x;
        }
        
        position.x += overlap.x;

        velocity.x = 0;
        break;
    }
    
    position.z += velocity.z;
    
    box.update(position);
    for(AABB & boxe : nearBoxes) {
        if(!getColliding(boxe)) {
            continue;
        }

        glm::vec3 minBox =  boxe.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox =  boxe.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 minBox2 = box.getVP(glm::vec3(1.f)/2.f);
        glm::vec3 maxBox2 = box.getVN(glm::vec3(1.f)/2.f);
        glm::vec3 overlap = glm::vec3(0.0f);

        if(velocity.z < 0) {
            overlap.z = maxBox.z - minBox2.z;
        } else {
            overlap.z = minBox.z - maxBox2.z;
        }
        
        position.z += overlap.z;

        

        velocity.z = 0;
        break;
    }
    
    nearBoxes.clear();
}

bool DYNAMIC_ENTITY::getColliding( AABB & boxe) {
    box.update(position);
    glm::vec3 minBox =  boxe.getVP(glm::vec3(1.f) /2.f);
    glm::vec3 maxBox =  boxe.getVN(glm::vec3(1.f)/2.f);
    glm::vec3 minBox2 = box.getVP(glm::vec3(1.f)/2.f);
    glm::vec3 maxBox2 = box.getVN(glm::vec3(1.f)/2.f);

    


    if(minBox.x >= maxBox2.x || maxBox.x <= minBox2.x) {
        return false;
    }
    if(minBox.y >= maxBox2.y || maxBox.y <= minBox2.y) {
        return false;
    }
    if(minBox.z >= maxBox2.z || maxBox.z <= minBox2.z) {
        return false;
    }
    return true;
}