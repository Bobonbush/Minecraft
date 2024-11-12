#include "rigidbody.h"



// HitBox3D

std::unique_ptr<CubeRenderer> HitBox3D::cubeRenderer = nullptr;

HitBox3D::HitBox3D(std::shared_ptr<Shader> shader) : shader(shader) {
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
Rigidbody::Rigidbody(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float mass, float drag, float angularDrag, bool useGravity, std::shared_ptr<Shader> shader) : hitBox(shader) {
   
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
    inverseMass = 1 / mass;
}


glm::vec3 Rigidbody::getDirectionCollide(glm::vec3 target, glm::vec3 & otherScale) {
    float max = 0.0f;
    glm::vec3 result = glm::vec3(0.0f, 0.0f, 0.0f);
    int Direction = 0;
    for (int i = 0; i < 6; i++) {
        glm::vec3 real_target = target + scale / 2.f * compass[i];
        real_target = target - otherScale /2.f *compass[i];
        float dot = glm::dot(real_target, compass[i]);
        if (dot > max) {
            max = dot;
            result = compass[i];
            Direction = i;
        }
    }  

    if(FaceCollision[Direction]) {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
    FaceCollision[Direction] = true;
    return result;     
}



// Only Accept Normal Coordinate Force
void Rigidbody::ApplyForce(glm::vec3 force) {
    force = force * physicConstant -> getConstantOffset();
    this->force += force;
}

void Rigidbody::AddInternalForce(glm::vec3 force) {
    InternalForce += force ;
}

void Rigidbody::ApplyInternalForce() {
    force += InternalForce * physicConstant -> getConstantOffset();
    InternalForce = glm::vec3(0.0f, 0.0f, 0.0f);
}



void Rigidbody::UpdateVelocity () {
    glm::vec3 VelocityMag = force * inverseMass ;

    velocity += VelocityMag;
    
    force = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Rigidbody::CollisionDetection(std::vector<std::shared_ptr<Rigidbody>> & rigidbodies) {
    FaceCollision = {false, false, false, false, false, false};


    for (auto &rigidbody : rigidbodies) {
        if (AABBIntersect(*rigidbody)) {
            ResolveCollision(*rigidbody);
        }
    }
}

void Rigidbody::ResolveCollision(Rigidbody & other) {
    



    glm::vec3 difference = position - other.position;
    glm::vec3 direction = getDirectionCollide(difference, other.scale);
    if(direction == glm::vec3(0.0f, 0.0f, 0.0f)) return;
    glm::vec3 VelocityDiff = velocity - other.velocity;
    glm::vec3 StopForce = glm::dot(VelocityDiff, direction) * direction * mass;
    force -= StopForce;

     glm::vec3 maxxA = position + scale / 2.f;
    glm::vec3 minxA = position - scale / 2.f;
    glm::vec3 maxxB = other.position + other.scale / 2.f;
    glm::vec3 minxB = other.position - other.scale / 2.f;

    glm::vec3 minV = glm::max(minxA, minxB);
    glm::vec3 maxV = glm::min(maxxA, maxxB);

    glm::vec3 penetration = minV - maxV;

    
    glm::vec3 correction = penetration * -direction;
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
    
}

void Rigidbody::FixedUpdate(float Alpha, std::vector<std::shared_ptr<Rigidbody> > & rigidbodies) {
    if(useGravity) {
        ApplyForce(glm::vec3(0.0f, - physicConstant -> getGravity() * mass , 0.0f));
    }else {
        velocity.y = 0;
    }

    UpdateVelocity();
    CollisionDetection(rigidbodies);
    UpdateVelocity();

    ApplyInternalForce();

    UpdateVelocity();

    
    glm::vec3 RealVelocity = velocity  ;
    //velocity = SPA::lerp(lastVelocity, velocity, Alpha);

    
    SPA::ConvertToNDCUnit(RealVelocity);
    
    position += RealVelocity ;

    position = SPA::lerp(lastPosition, position, Alpha);
    
    // Default Drag Force
    float friction = 0.95f;
    SPA::clamp(friction, 0.0f, 1.0f);
    //std::cout << friction << std::endl;
    velocity.x *= friction;
    velocity.z *= friction;
    if(glm::length(velocity) < 0.01f) {
        velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    lastPosition = position;
    lastVelocity = velocity;
}