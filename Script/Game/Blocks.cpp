#include "Blocks.h"


// BLOCK

Block::Block(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    textureManager = TextureManager::getInstance();

}

Block::~Block() {
}

void Block::Render(glm:: mat4 view, glm::mat4 projection) {
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

void Block::Update(float deltaTime) {
    
}


// DIRT BLOCK

std::unique_ptr<CubeRenderer> Dirt::cubeRenderer = nullptr;
Dirt::Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    
    texture =  textureManager -> LoadTexture("Assets/dirt.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        cubeRenderer -> LoadCube(texture);
    }
}

Dirt::~Dirt() {
}

void Dirt::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Dirt::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection);
}


// STONE BLOCK
std::unique_ptr<CubeRenderer> Stone::cubeRenderer = nullptr;
Stone::Stone(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/stone.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        cubeRenderer -> LoadCube(texture);
    }
}

Stone::~Stone() {
}

void Stone::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Stone::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection);
}

// WATER BLOCK

std::unique_ptr<CubeRenderer> Water::cubeRenderer = nullptr;

Water:: Water(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/water.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        cubeRenderer -> LoadCube(texture);
    }
}

Water::~Water() {
}

void Water::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Water::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection);
}

// SAND BLOCK

std::unique_ptr<CubeRenderer> Sand::cubeRenderer = nullptr;

Sand::Sand(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = textureManager -> LoadTexture("Assets/sand.png");
    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        cubeRenderer -> LoadCube(texture);
    }
}

Sand::~Sand() {
}

void Sand::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Sand::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection);
}

// GRASS BLOCK

std::unique_ptr<CubeRenderer> Grass::cubeRenderer = nullptr;

Grass::Grass(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    textureTop = textureManager -> LoadTexture("Assets/Grass/Top.png");
    textureSide = textureManager -> LoadTexture("Assets/Grass/Side.png");
    textureBottom = textureManager -> LoadTexture("Assets/Grass/dirt.png");

    if(cubeRenderer == nullptr) {
        cubeRenderer = std::make_unique<CubeRenderer>(shader);
        cubeRenderer -> LoadCube(textureTop, textureSide, textureBottom);
    }
    
}

Grass::~Grass() {
}

void Grass::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Grass::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
    cubeRenderer -> Render(position, scale, rotation, view, projection);
}


