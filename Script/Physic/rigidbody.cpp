#include "rigidbody.h"



// HitBox3D

std::unique_ptr<CubeRenderer> HitBox3D::cubeRenderer = nullptr;

HitBox3D::HitBox3D(Shader &shader) : shader(shader) {
    if(!cubeRenderer ) cubeRenderer =  std::make_unique<CubeRenderer>(shader);
    TextureManager *textureManager = TextureManager::getInstance();
    cubeRenderer -> LoadCube(textureManager -> LoadTexture("Assets/HitBox.png"));
    
}

HitBox3D::~HitBox3D() {
}

void HitBox3D::ShowHitBox(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3> &validPositions) {
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
}






// Rigidbody
Rigidbody::Rigidbody(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float mass, float drag, float angularDrag, bool useGravity, Shader &shader) : hitBox(shader) {
   
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

void Rigidbody::CollisionDetection(std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    for (auto &rigidbody : rigidbodies) {
        if (AABBIntersect(*rigidbody)) {
            ResolveCollision(*rigidbody);
        }
    }
}

void Rigidbody::ResolveCollision(Rigidbody & other) {
    glm::vec3 difference = position - other.position;
    glm::vec3 direction = getDirectionCollide(difference);
    glm::vec3 VelocityDiff = velocity - other.velocity;

    glm::vec3 normalForce = glm::dot(VelocityDiff, direction) * direction * mass;
    force -= normalForce;
    
    glm::vec3 penetration = glm::abs(difference) - (scale + other.scale) /2.f;
    //glm::vec3 correction = glm::clamp(penetration, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    glm::vec3 correction = penetration *  (-direction);
    position += correction;
    //force += normalForce;



}

bool Rigidbody::AABBIntersect(const Rigidbody& other) {
    bool overLapX = (position.x + scale.x >= other.position.x) && (other.position.x + other.scale.x >= position.x);
    bool overLapY = (position.y + scale.y >= other.position.y) && (other.position.y + other.scale.y >= position.y);
    bool overLapZ = (position.z + scale.z >= other.position.z) && (other.position.z + other.scale.z >= position.z);

    return overLapX && overLapY && overLapZ;
}

void Rigidbody::Update(float deltaTime, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    if(useGravity) {
        ApplyForce(glm::vec3(0.0f, - physicConstant -> getGravity() * mass , 0.0f));
    }

    glm::vec3 VelocityMag = force/mass;

    velocity += VelocityMag;
    
    force = glm::vec3(0.0f, 0.0f, 0.0f);

    CollisionDetection(rigidbodies);

    VelocityMag = force/mass;
    

    velocity += VelocityMag;

    
    
    glm::vec3 RealVelocity = velocity * deltaTime;
    SPA::ConvertToNDCUnit(RealVelocity);
    
    position += RealVelocity; 
    //std::cout << RealVelocity.x << " " << RealVelocity.y << " " << RealVelocity.z << std::endl;


    force = glm::vec3(0.0f, 0.0f, 0.0f);
}