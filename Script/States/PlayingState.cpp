#include "PlayingState.h"

bool PlayingState::pressed[256];
PlayingState * PlayingState::m_instance = nullptr;

PlayingState::PlayingState() {
    for(int i = 0 ; i < 256 ; i++) {
        pressed[i] = false;
    }
    player = Player::GetInstance();
    cursor = Cursor::GetInstance();
    glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
}

PlayingState::~PlayingState() {
    delete m_instance;
}

void PlayingState::ProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    MouseProcess(camera, chunkManager, view, projection);
}

void PlayingState::MouseProcess(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection) {
    int input = cursor -> GetInput();



    std::vector<glm::vec3> normal = Block::normals;




    Ray ray = Ray(camera);

    bool exists = false;
    glm::vec3 blockPosition = glm::vec3(0.f);
    glm::vec3 nearestRay;
    
    for(int i = 0 ; i < 300 ; i++) {
        float step_size = 0.025;
        ray.step(step_size);
        glm::vec3 position = ray.getRayEnd();
        nearestRay = position;
        
            //std::cout << x <<  " " << y << " " << z << std::endl;
        if(chunkManager.existsBlock(position.x, position.y, position.z)) {
                //std::cout << x <<  " " << y << " " << z << std::endl;
            exists = true;
            blockPosition = chunkManager.getBlockPosition(position.x, position.y, position.z);
            hitBox.Draw(blockPosition, glm::vec3(1.f), view, projection);
            break;
        }
    }

    if(exists == false) return ;

    if(input == Cursor::MOUSE_EVENT::LEFT_CLICK) {
        chunkManager.removeBlock(blockPosition.x, blockPosition.y, blockPosition.z);
    }

    if(input == Cursor::MOUSE_EVENT::RIGHT_CLICK) {
        glm::vec3 position = blockPosition;
        //glm::vec3 normalize = glm::vec3(0.f);
        float distance = 10000.f;
        for(int i = 0 ; i < 6 ; i++) {
            glm::vec3 surface = normal[i] + blockPosition;
            float dist = glm::distance(surface, nearestRay);
            if(dist < distance) {
                distance = dist;
                position = surface;
            }
        }
        

        chunkManager.addBlock(position.x, position.y, position.z, ChunkBlock(BLOCKID::Grass));
    }

    //glDisable(GL_BLEND);
    
}

void PlayingState::FixedProcessState(const Camera & camera, ChunkManager & chunkManager, const glm::mat4 & view, const glm::mat4 & projection)  {

    for(int i = 0 ; i < 256 ; i++) {
        if( i == GLFW_KEY_C && pressed[i] == true && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) == GLFW_RELEASE) {
            player -> setFlying(!player -> Flying());
            pressed[i] = false;
        }

        if(glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS) {
            pressed[i] = true;
        }
    }

    glm::vec3 force = glm::vec3(0.f);
    float elapsedTime = 1.f;
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::FORWARD, elapsedTime);
    }
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::BACKWARD, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::LEFT, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        force += camera.ProcessKeyboard(Camera_Movement::RIGHT, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS && player -> Flying()) {
        force += camera.ProcessKeyboard(Camera_Movement::UP, elapsedTime);
    }
    
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && player -> Flying()) {
        force += camera.ProcessKeyboard(Camera_Movement::DOWN, elapsedTime);
    }

    

    player -> addForce(force);
}
