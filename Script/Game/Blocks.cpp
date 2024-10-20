#include "Blocks.h"



// HitBox3D
std::unique_ptr<CubeRenderer> HitBox3D::cubeRenderer = nullptr;
HitBox3D::HitBox3D(Shader &shader) {
    TextureManager *textureManager = TextureManager::getInstance();
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        
    }
    cubeRenderer -> LoadCube(textureManager -> LoadTexture("Assets/hitbox.png"));
}

HitBox3D::~HitBox3D() {
}

void HitBox3D::ShowHitBox(glm::mat4 view, glm::mat4 projection, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::vector<glm::vec3> &validPositions) {
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
}




// BLOCK

Block::Block(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    textureManager = TextureManager::getInstance();
    Box = std::make_unique<HitBox3D>(shader);
}

Block::~Block() {
}

void Block::SetPosition(glm::vec3 position) {
    this->position = position;
}


void Block::SetScale(glm::vec3 scale) {
    this->scale = scale;
}

void Block::SetRotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

glm::vec3 Block::GetPosition() {
    return position;
}

glm::vec3 Block::GetScale() {
    return scale;
}

glm::vec3 Block::GetRotation() {
    return rotation;
}



void Block::PrepareRender(Frustum frustum) {
}

void Block::Render(glm::mat4 view, glm::mat4 projection) {

}

void Block::Update(float deltaTime) {
    
}

bool Block::FrustumCulling(const Frustum frustum) {
    glm::vec3 blockMin = position - scale / 2.f; // Minimum corner of the block
    glm::vec3 blockMax = position + scale / 2.f; // Maximum corner of the block

    // Check each plane of the frustum
    if (frustum.leftFace.distance + glm::dot(frustum.leftFace.normal, blockMin) < 0 &&
        frustum.leftFace.distance + glm::dot(frustum.leftFace.normal, blockMax) < 0) {
        
        return false; // Block is outside the left face
    }

    if (frustum.rightFace.distance + glm::dot(frustum.rightFace.normal, blockMax) < 0 &&
        frustum.rightFace.distance + glm::dot(frustum.rightFace.normal, blockMin) < 0) {
            //std::cout << "Fuck" << '\n';
        return false; // Block is outside the right face
        
    }

    if (frustum.topFace.distance + glm::dot(frustum.topFace.normal, blockMax) < 0 &&
        frustum.topFace.distance + glm::dot(frustum.topFace.normal, blockMin) < 0) {
        return false; // Block is outside the top face
    }

    if (frustum.bottomFace.distance + glm::dot(frustum.bottomFace.normal, blockMin) < 0 &&
        frustum.bottomFace.distance + glm::dot(frustum.bottomFace.normal, blockMax) < 0) {
        return false; // Block is outside the bottom face
    }
    


    if (frustum.farFace.distance + glm::dot(frustum.farFace.normal, blockMin) < 0 &&
        frustum.farFace.distance + glm::dot(frustum.farFace.normal, blockMax) < 0) {
        return false; // Block is behind the far face
    }


    

    // If the block is not outside any planes, it's in the frustum
    return true;
}

// DIRT BLOCK

std::unique_ptr<CubeRenderer> Dirt::cubeRenderer = nullptr;
std::vector<glm::vec3> Dirt::validPositions;
Dirt::Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    
    texture =  textureManager -> LoadTexture("Assets/dirt.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        
    }
    cubeRenderer -> LoadCube(texture);
    
}

Dirt::~Dirt() {
}

void Dirt::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Dirt::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
         validPositions.push_back(position);
    }
}

void Dirt::Render(glm::mat4 view, glm::mat4 projection) {

    
    if((int) validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    Box -> ShowHitBox(view, projection, position, scale, rotation, validPositions);
    validPositions.clear();
}


//STONE BLOCK


std::unique_ptr<CubeRenderer> Stone::cubeRenderer = nullptr;
std::vector<glm::vec3> Stone::validPositions;
Stone::Stone(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/Stone.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
    }

    cubeRenderer -> LoadCube(texture);
}

Stone::~Stone() {
}

void Stone::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Stone::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
       validPositions.push_back(position);
    }

     
}

void Stone::Render(glm::mat4 view, glm::mat4 projection) {
   
    if( (int) validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);

    //std::cout << "YES" <<'\n';
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    Box -> ShowHitBox(view, projection, position, scale, rotation, validPositions);
    validPositions.clear();
}

// WATER BLOCK

std::unique_ptr<CubeRenderer> Water::cubeRenderer = nullptr;
std::vector<glm::vec3> Water::validPositions;

Water:: Water(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/water.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
    }
    cubeRenderer -> LoadCube(texture);
}

Water::~Water() {
}

void Water::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Water::Render(glm::mat4 view, glm::mat4 projection) {
    
    if( (int)validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    validPositions.clear();
}

void Water::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
        validPositions.push_back(position);
    }
    
}

// SAND BLOCK

std::unique_ptr<CubeRenderer> Sand::cubeRenderer = nullptr;
std::vector<glm::vec3> Sand::validPositions;

Sand::Sand(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/sand.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
    }
    
    cubeRenderer -> LoadCube(texture);
}

Sand::~Sand() {
}

void Sand::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Sand::Render(glm::mat4 view, glm::mat4 projection) {
    
    if((int) validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    Box -> ShowHitBox(view, projection, position, scale, rotation, validPositions);
    validPositions.clear();
}

void Sand::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
        validPositions.push_back(position);
    }
    
}

// GRASS BLOCK

std::unique_ptr<CubeRenderer> Grass::cubeRenderer = nullptr;
std::vector<glm::vec3> Grass::validPositions;

Grass::Grass(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    textureTop = textureManager -> LoadTexture("Assets/Grass/Top.png");
    textureSide = textureManager -> LoadTexture("Assets/Grass/Side.png");
    textureBottom = textureManager -> LoadTexture("Assets/Grass/dirt.png");

    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
    }

    cubeRenderer -> LoadCube(textureTop, textureSide, textureBottom);
    
}

Grass::~Grass() {
}

void Grass::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Grass::Render(glm::mat4 view, glm::mat4 projection) {
    
    if(validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    Box -> ShowHitBox(view, projection, position, scale, rotation, validPositions);
    validPositions.clear();
}

void Grass::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
        validPositions.push_back(position);
    }
    
}
