#ifndef CAMERA_H
#define CAMERA_H
#include "Texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"




// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
enum class  Camera_Movement : int {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods


// Default camera values
    static const float YAW ;      
    static const float PITCH;      
    const float SPEED       =  0.55f;
    const float SENSITIVITY =  0.2f;
    const float ZOOM        =  45.0f;
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    Entity * attachedEntity = nullptr;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void AttachEntity(Entity * entity) {
        attachedEntity = entity;
    }

    void update() {
        if(attachedEntity != nullptr) {
            Position = attachedEntity -> getPosition();
        }
        //attachedEntity -> addForce(glm::vec3(0.0f, -9.8f, 0.0f));
    }

    void FixedUpdate() {
        float elapsedTime = 1.f;
        
        glm::vec3 force = glm::vec3(0.0f);
        
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::FORWARD, elapsedTime);
        }
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::BACKWARD, elapsedTime);
        }
    
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::LEFT, elapsedTime);
        }
    
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::RIGHT, elapsedTime);
        }
    
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::UP, elapsedTime);
        }
    
        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            force += ProcessKeyboard(Camera_Movement::DOWN, elapsedTime);
        }
        if(attachedEntity != nullptr)
            attachedEntity -> addForce(force);
        else {
            Position += force;
        }
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    glm::vec3 & ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == Camera_Movement::FORWARD)
            return Front * velocity;
        if (direction == Camera_Movement::BACKWARD)
            return  -Front * velocity;
        if (direction == Camera_Movement::LEFT)
            return - Right * velocity;
        if (direction == Camera_Movement::RIGHT)
            return Right * velocity;
        if(direction == Camera_Movement::UP)
            return  glm::vec3(0.f, 1.f, 0.f) * velocity;
        if(direction == Camera_Movement::DOWN)
            return - glm::vec3(0.f , 1.f, 0.f) * velocity;
        return glm::vec3(0.0f);
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};


#endif