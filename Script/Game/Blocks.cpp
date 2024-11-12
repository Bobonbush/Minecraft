#include "Blocks.h"





// BLOCK



Block::Block(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::shared_ptr<Shader> shader) : shader(shader) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    textureManager = TextureManager::getInstance();
    rigidbody = std::make_shared<Rigidbody>(position, scale, rotation, 1, 0, 0, false, shader);
    PhysicConstant * physicConstant = PhysicConstant::getInstance();
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


void Block::PrepareRender(int mask) {
}

void Block::Render(glm::mat4 view, glm::mat4 projection) {
    
}

void Block::Update(float deltaTime) {
    
}
// DIRT BLOCK

std::unique_ptr<CubeRenderer> Dirt::cubeRenderer = nullptr;
std::vector<glm::vec3> Dirt::validPositions;
std::vector<int> Dirt::banFace;
Dirt::Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::shared_ptr<Shader> shader) : Block(position, scale, rotation, shader) {
    
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

void Dirt::PrepareRender(int mask) {
    validPositions.push_back(position);
    banFace.push_back(mask);
    
}

void Dirt::Render(glm::mat4 view, glm::mat4 projection) {

    
    if((int) validPositions.size() == 0) {
        return;
    }
    Block::Render(view, projection);
    if(ShowHitBox == true) {
        rigidbody -> ShowHitBox(view, projection, validPositions);
    }
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    
    validPositions.clear();
    banFace.clear();
}


//STONE BLOCK

std::unique_ptr<CubeRenderer> Stone::cubeRenderer = nullptr;
std::vector<glm::vec3> Stone::validPositions;
std::vector<int> Stone::banFace;
Stone::Stone(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::shared_ptr<Shader> shader) : Block(position, scale, rotation, shader) {
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

void Stone::PrepareRender( int mask) {
    Block::PrepareRender(mask);

    validPositions.push_back(position);
    banFace.push_back(mask);
    
}

void Stone::Render(glm::mat4 view, glm::mat4 projection) {
   
    if( (int) validPositions.size() == 0) {
        return;
    }

    //CullingValidPosition(validPositions, banFace);
    //std::cout << "BlockSize : " << validPositions.size() << '\n';
    Block::Render(view, projection);

     if(ShowHitBox == true) {
        rigidbody -> ShowHitBox(view, projection, validPositions);
    }

    //std::cout << "YES" <<'\n';
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions, banFace);
    validPositions.clear();
    banFace.clear();
}

// WATER BLOCK

std::unique_ptr<CubeRenderer> Water::cubeRenderer = nullptr;
std::vector<glm::vec3> Water::validPositions;
std::vector<int> Water::banFace;
Water:: Water(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation,std::shared_ptr<Shader> shader) : Block(position, scale, rotation, shader) {
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

    //CullingValidPosition(validPositions, banFace);
    Block::Render(view, projection);

     if(ShowHitBox == true) {
        rigidbody -> ShowHitBox(view, projection, validPositions);
    }
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions, banFace);
    validPositions.clear();
    banFace.clear();
}

void Water::PrepareRender( int mask) {
    Block::PrepareRender( mask);

    validPositions.push_back(position);
    banFace.push_back(mask);
    
    
}

// SAND BLOCK
/*

std::unique_ptr<CubeRenderer> Sand::cubeRenderer = nullptr;
std::vector<glm::vec3> Sand::validPositions;

Sand::Sand(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::shared_ptr<Shader> shader) : Block(position, scale, rotation, shader) {
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

     if(ShowHitBox == true) {
        rigidbody -> ShowHitBox(view, projection, validPositions);
    }
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
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

Grass::Grass(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::shared_ptr<Shader> shader) : Block(position, scale, rotation, shader) {
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

     if(ShowHitBox == true) {
        rigidbody -> ShowHitBox(view, projection, validPositions);
    }
    cubeRenderer -> Render(position, scale, rotation, view, projection, validPositions);
    validPositions.clear();
}

void Grass::PrepareRender(Frustum frustum) {
    Block::PrepareRender(frustum);
    if(FrustumCulling(frustum)) {
        validPositions.push_back(position);
    }
    
}
*/