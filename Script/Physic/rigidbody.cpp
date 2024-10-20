#include "rigidbody.h"

std::vector<std::shared_ptr<Rigidbody>> Rigidbody::rigidbodies;



Rigidbody::Rigidbody(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float mass, float drag, float angularDrag, bool useGravity) {
   
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;

    this->mass = mass;
    this->drag = drag;
    this->angularDrag = angularDrag;
    this->useGravity = useGravity;

    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    force = glm::vec3(0.0f, 0.0f, 0.0f);
    physicConstant = PhysicConstant::getInstance();
}


// Only Accept Normal Coordinate Force
void Rigidbody::ApplyForce(glm::vec3 force) {
    force = force * physicConstant -> getConstantOffset();
    this->force += force;
}

void Rigidbody::AABBDetection() {
    std::sort(rigidbodies.begin(), rigidbodies.end(), [](const std::shared_ptr<Rigidbody>& a, const std::shared_ptr<Rigidbody>& b) {
        return a->position.x < b->position.x;
    });


    std::set<std::shared_ptr<Rigidbody>> xSorted;
    std::set<std::shared_ptr<Rigidbody>> eraseSet;
    for (int i = 0; i < rigidbodies.size(); i++) {
        for (auto it = xSorted.begin(); it != xSorted.end(); it++) {
            if(rigidbodies[i] -> position.x  + rigidbodies[i] -> scale.x < rigidbodies[i] -> position.x) {
                eraseSet.insert(rigidbodies[i]);
            }
        }

        xSorted.insert(rigidbodies[i]);
    }
}


bool Rigidbody::AABBIntersect(const Rigidbody& other) {
    return position.x < other.position.x + other.scale.x &&
        position.x + scale.x > other.position.x &&
        position.y < other.position.y + other.scale.y &&
        position.y + scale.y > other.position.y &&
        position.z < other.position.z + other.scale.z &&
        position.z + scale.z > other.position.z;
}

void Rigidbody::Update(float deltaTime) {
    if(useGravity) {
        ApplyForce(glm::vec3(0.0f, - physicConstant -> getGravity() * mass , 0.0f));
    }

    glm::vec3 VelocityMag = force/mass * deltaTime;
    SPA::ConvertToNDCUnit(VelocityMag);

    velocity += VelocityMag;


    position += velocity * deltaTime;


    force = glm::vec3(0.0f, 0.0f, 0.0f);
}