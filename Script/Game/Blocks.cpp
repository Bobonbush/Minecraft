#include "Blocks.h"







void Frustum::normalize(glm::vec4 & plane) {
    float distance = glm::length(glm::vec3(plane));
    plane /= distance;
    return ;
}

void Frustum::update() {
        Player * player = Player::getInstance();
        Setting * settings = Setting::getInstance();
        glm::mat4 view = player -> getViewMatrix();
        glm::mat4 projection = player -> getProjectionMatrix(settings -> getResolution().x , settings -> getResolution().y);
        glm::mat4 viewProjMatrix =  projection * view ;
        
        planes[0].x = viewProjMatrix[0][3] + viewProjMatrix[0][0];
        planes[0].y = viewProjMatrix[1][3] + viewProjMatrix[1][0];
        planes[0].z = viewProjMatrix[2][3] + viewProjMatrix[2][0];
        planes[0].w = viewProjMatrix[3][3] + viewProjMatrix[3][0];

        normalize(planes[0]);
        //std::cout << "Right : " << planes[0].x << ", " << planes[0].y << ", " << planes[0].z << ", " << planes[0].w  << '\n';

       



        planes[1].x = viewProjMatrix[0][3] - viewProjMatrix[0][0];
        planes[1].y = viewProjMatrix[1][3] - viewProjMatrix[1][0];
        planes[1].z = viewProjMatrix[2][3] - viewProjMatrix[2][0];
        planes[1].w = viewProjMatrix[3][3] - viewProjMatrix[3][0];
        normalize(planes[1]);

        
        

        //std::cout << "Left : " << planes[1].x << ", " << planes[1].y << ", " << planes[1].z<< ", " << planes[1].w  << '\n';
        
        planes[2].x = viewProjMatrix[0][3] - viewProjMatrix[0][1];
        planes[2].y = viewProjMatrix[1][3] - viewProjMatrix[1][1];
        planes[2].z = viewProjMatrix[2][3] - viewProjMatrix[2][1];
        planes[2].w = viewProjMatrix[3][3] - viewProjMatrix[3][1];
        normalize(planes[2]);

        

       // std::cout << "Bottom : " << planes[2].x << ", " << planes[2].y << ", " << planes[2].z<< ", " << planes[2].w <<  '\n';
        
        planes[3].x = viewProjMatrix[0][3] + viewProjMatrix[0][1];
        planes[3].y = viewProjMatrix[1][3] + viewProjMatrix[1][1];
        planes[3].z = viewProjMatrix[2][3] + viewProjMatrix[2][1];
        planes[3].w = viewProjMatrix[3][3] + viewProjMatrix[3][1];
        normalize(planes[3]);

    
        
        

        //std::cout << "Top : " << planes[3].x << ", " << planes[3].y << ", " << planes[3].z<< ", " << planes[3].w <<  '\n';
        
        planes[4].x = viewProjMatrix[0][3] + viewProjMatrix[0][2];
        planes[4].y = viewProjMatrix[1][3] + viewProjMatrix[1][2];
        planes[4].z = viewProjMatrix[2][3] + viewProjMatrix[2][2];
        planes[4].w = viewProjMatrix[3][3] + viewProjMatrix[3][2];
        normalize(planes[4]);
        
        

        //std::cout << "Near : " << planes[4].x << ", " << planes[4].y << ", " << planes[4].z << "," << planes[4].w << '\n';
        
        planes[5].x = viewProjMatrix[0][3] - viewProjMatrix[0][2];
        planes[5].y = viewProjMatrix[1][3] - viewProjMatrix[1][2];
        planes[5].z = viewProjMatrix[2][3] - viewProjMatrix[2][2];
        planes[5].w = viewProjMatrix[3][3] - viewProjMatrix[3][2];
        normalize(planes[5]);

        //std::cout << "Far : " << planes[5].x << ", " << planes[5].y << ", " << planes[5].z << ", " << planes[5].w << '\n';
        
}

const bool Frustum::isChunkInFrustum(const glm::vec3 & origin, float chunkSize){
            glm::vec3 min = origin - glm::vec3(chunkSize /2.f) ;
            glm::vec3 max = origin + glm::vec3(chunkSize /2.f) ;
            max.y += chunkSize / 2.f;
            min.y += chunkSize / 2.f;
            
            for(int i = 0; i < 6 ; i++) {
                int out = 0;
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, min.z, 1.f))  < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                if(out == 8) {
                    return false;
                }
            }
            /*
            int out = 0;
            
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x > max.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x < min.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y > max.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y < min.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z > max.z)? 1 : 0); if(out == 8) return false;

            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z < min.z)? 1 : 0); if(out == 8) return false;
            */
            
            return true;
        }

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
    
    frustum.update();
    
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
    Block::PrepareRender(mask);
    Setting * settings = Setting::getInstance();
    glm::vec3 checkPosition = position;
    checkPosition.y -= settings -> getBlockNDCSize().y / 1.5f;
    if(frustum.isChunkInFrustum(checkPosition, settings -> getBlockNDCSize().x)) {
        validPositions.push_back(position);
        banFace.push_back(mask);
        return ;
    }
    
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
    Block::PrepareRender(validPositions.empty());
    Setting * settings = Setting::getInstance();
    glm::vec3 checkPosition = position;
    checkPosition.y -= settings -> getBlockNDCSize().y / 2.f;
    if(frustum.isChunkInFrustum(checkPosition, settings -> getBlockNDCSize().x)) {
        validPositions.push_back(position);
        banFace.push_back(mask);
        return ;
    }
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
    Block::PrepareRender(mask);
    Setting * settings = Setting::getInstance();
    glm::vec3 checkPosition = position;
    checkPosition.y -= settings -> getBlockNDCSize().y / 2.f;
    if(frustum.isChunkInFrustum(checkPosition, settings -> getBlockNDCSize().x)) {
        validPositions.push_back(position);
        banFace.push_back(mask);
        return ;
    }

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