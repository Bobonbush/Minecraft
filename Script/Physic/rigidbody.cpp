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


glm::vec3 Rigidbody::getDirectionCollide(glm::vec3 target) {
            float max = 0.0f;
            glm::vec3 result = glm::vec3(0.0f, 0.0f, 0.0f);
            int Direction = 0;
            for (int i = 0; i < 6; i++) {
                float dot = glm::dot(target, compass[i]);
                if (dot > max) {
                    max = dot;
                    result = compass[i];
                    Direction = i;
                }
            }  
            if(FaceCollision[Direction]) return glm::vec3(0.0f, 0.0f, 0.0f);
            FaceCollision[Direction] = true; 
            return result;     
        }

// Only Accept Normal Coordinate Force
void Rigidbody::ApplyForce(glm::vec3 force) {
    force = force * physicConstant -> getConstantOffset();
    this->force += force;
}

void Rigidbody::AddInternalForce(glm::vec3 force) {
    InternalForce += force * physicConstant -> getConstantOffset();
}

void Rigidbody::ApplyInternalForce() {
    force += InternalForce;
    InternalForce = glm::vec3(0.0f, 0.0f, 0.0f);
}



void Rigidbody::UpdateVelocity (float deltaTime) {
    glm::vec3 VelocityMag = force/mass;

    velocity += VelocityMag;
    
    force = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Rigidbody::CollisionDetection(std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    FaceCollision = {false, false, false, false, false, false};
    for (auto &rigidbody : rigidbodies) {
        if (AABBIntersect(*rigidbody)) {
            ResolveCollision(*rigidbody);
            break;
        }
    }
}

void Rigidbody::ResolveCollision(Rigidbody & other) {
    glm::vec3 difference = position - other.position;
    glm::vec3 direction = getDirectionCollide(difference);
    glm::vec3 VelocityDiff = velocity - other.velocity;

    glm::vec3 StopForce = glm::dot(VelocityDiff, direction) * direction * mass;
    force -= StopForce;
    
    glm::vec3 penetration = glm::abs(difference) - (scale + other.scale) /2.f;
    //glm::vec3 correction = glm::clamp(penetration, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    glm::vec3 correction = penetration *  (-direction);
    position += correction;
    //force += normalForce;



}

bool Rigidbody::AABBIntersect(const Rigidbody& other) {
    glm::vec3 min = position - scale / 2.f;
    glm::vec3 max = position + scale / 2.f;

    glm::vec3 otherMin = other.position - other.scale / 2.f;
    glm::vec3 otherMax = other.position + other.scale / 2.f;

    return (min.x <= otherMax.x && max.x >= otherMin.x) &&
           (min.y <= otherMax.y && max.y >= otherMin.y) &&
           (min.z <= otherMax.z && max.z >= otherMin.z);
}

void Rigidbody::Update(float deltaTime, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    if(useGravity) {
        ApplyForce(glm::vec3(0.0f, - physicConstant -> getGravity() * mass * deltaTime , 0.0f));
    }

    UpdateVelocity(deltaTime);
    CollisionDetection(rigidbodies);
    UpdateVelocity(deltaTime);

    ApplyInternalForce();

    UpdateVelocity(deltaTime);
    
    glm::vec3 RealVelocity = velocity ;
    SPA::ConvertToNDCUnit(RealVelocity);
    
    position += RealVelocity ; 
    //std::cout << RealVelocity.x << " " << RealVelocity.y << " " << RealVelocity.z << std::endl;

    

    force = glm::vec3(0.0f, 0.0f, 0.0f);
}