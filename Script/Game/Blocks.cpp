#include "Blocks.h"


// BLOCK

Block::Block(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    cubeRenderer = new CubeRenderer(shader);
}

Block::~Block() {
    delete cubeRenderer;
}

void Block::Render(glm:: mat4 view, glm::mat4 projection) {
    cubeRenderer->Render(position, scale, rotation, view , projection);
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

Dirt::Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader) : Block(position, scale, rotation, shader) {
    texture = TextureLoader::LoadTexture("Assets/dirt.png");
    cubeRenderer -> LoadCube(texture);
}

Dirt::~Dirt() {
}

void Dirt::Update(float deltaTime) {
    Block::Update(deltaTime);
}

void Dirt::Render(glm::mat4 view, glm::mat4 projection) {
    Block::Render(view, projection);
}