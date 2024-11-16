#include "skybox.h"



// Planet Implementation

Planet::Planet (std::shared_ptr <Shader> shader ,char* path, glm::vec3 TimeZone) : TimeZone(TimeZone) {
    ShaderManager * shaderManager = ShaderManager::getInstance();
    TextureManager * textureManager = TextureManager::getInstance();
    
    
    texture = textureManager -> LoadTexture(path);
    cubeRenderer = std::make_unique<CubeSurface>(shader, 1, texture);
}

Planet::~Planet() {

}

void Planet::Render(glm::mat4 view, glm::mat4 projection) {
    
    Player * player = Player::getInstance();
    Setting * settings = Setting::getInstance();
    glm::vec3 CameraPosition = player -> GetPosition();
    

    
    position = CameraPosition + glm::vec3(
          distance * settings -> getBlockNDCSize().x * cos(settings -> getHour() + TimeZone.x * glm::pi<float>()),
          distance * settings -> getBlockNDCSize().x * sin(settings -> getHour() + TimeZone.y * glm::pi<float>()) , 
          0.0f);
    
    
    std::vector<glm::vec3> validPositions;
    validPositions.push_back(position);
    glm::mat4 viewWithoutTranslation = glm::mat4(glm::mat3(view));

    glm::vec3 direction = glm::normalize(CameraPosition - position);
    glm::vec3 bottomNormal = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 axis = glm::cross(bottomNormal, direction);

    float dotProduct = glm::dot(bottomNormal, direction);
    dotProduct = glm::clamp(dotProduct, -1.0f, 1.0f);
    float angle = glm::acos(dotProduct);


    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);


    
    cubeRenderer -> Render(position, glm::vec3(10.0f, 10.0f, 10.0f), rotation, view, projection, validPositions);
    ShaderManager * shaderManager = ShaderManager::getInstance();  

    float offsetDay = settings -> getOffsetDay();
    
    if(TimeZone == glm::vec3(0.0f, 0.0f, 0.0f)) {
        shaderManager -> GetShader("block") -> use();
        shaderManager -> GetShader("block") -> setVec3("lightPos", position);
        shaderManager -> GetShader("block") -> setVec3("lightColor", glm::vec3(0.8f, 0.8f, 1.f));
    
        //settings -> setHour(settings -> getHour() + 0.0001f);
    }else if(TimeZone != glm::vec3(0.0f, 0.0f, 0.0f)) {
        shaderManager -> GetShader("block") -> use();
        shaderManager -> GetShader("block") -> setVec3("lightPos", position);
        shaderManager -> GetShader("block") -> setVec3("lightColor", glm::vec3(0.4f, 0.4f, 0.6f));
    }
}


// Skybox

Skybox::Skybox() {

    
    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    std::vector<std::string> faces {
        "Assets/skybox/right.png",
        "Assets/skybox/left.png",
        "Assets/skybox/top.png",
        "Assets/skybox/bottom.png",
        "Assets/skybox/front.png",
        "Assets/skybox/back.png"
    };

    unsigned int cubemapTexture = TextureLoader::LoadCubeMap(faces);
    ShaderManager * shaderManager = ShaderManager::getInstance();
    shaderManager -> LoadShader("skybox", "Shaders/skybox.vs", "Shaders/skybox.fs");
    shaderManager -> LoadShader("lightSource", "Shaders/lightSource.vs", "Shaders/lightSource.fs");
    shader = shaderManager -> GetShader("skybox");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    sun = std::make_unique<Planet>(shaderManager -> GetShader("lightSource"),(char* ) "Assets/sun.png", glm::vec3(0.0f, 0.0f, 0.0f));
    moon = std::make_unique<Planet>(shaderManager -> GetShader("lightSource"),(char* ) "Assets/moon.png", glm::vec3(1.0f, 1.0f, 0.0f));
}

Skybox::~Skybox() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Skybox::Render(glm::mat4 view, glm::mat4 projection) {
    moon -> Render(view, projection);
    sun -> Render(view, projection);
    //moon -> Render(view, projection);
    glm::mat4 viewWithoutTranslation = glm::mat4(glm::mat3(view));
    
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    
    shader -> use();
    Setting * settings = Setting::getInstance();

    shader -> setMat4("view", viewWithoutTranslation);
    shader -> setMat4("projection", projection);
    
    
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    
}

