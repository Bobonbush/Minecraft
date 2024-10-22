#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Texture.h"
#include <memory>
#include <algorithm>
#include <set>
#include "Algorithm.h"

#include "PhysicVariable.h"
#include "Resource/TextureLoad.h"



class HitBox3D {
    
    private:
        static std::unique_ptr<CubeRenderer> cubeRenderer;
        Shader shader;
    public:
        HitBox3D(Shader &shader);
        ~HitBox3D();

        void ShowHitBox(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3> &validPositions);
};



class Rigidbody { 
    private :

        enum Face {
            FRONT = 0,
            BACK = 1,
            LEFT = 2,
            RIGHT = 3,
            TOP = 4,
            BOTTOM = 5
        };

        const glm::vec3 compass[6] = {
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
        };

        glm::vec3 getDirectionCollide(glm::vec3 target) {
            float max = 0.0f;
            glm::vec3 result = glm::vec3(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < 6; i++) {
                float dot = glm::dot(target, compass[i]);
                if (dot > max) {
                    max = dot;
                    result = compass[i];
                }
            }   
            return result;     
        }
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        float mass;
        float drag;
        float angularDrag;
        bool useGravity;

        glm::vec3 velocity;
        glm::vec3 angularVelocity;
        glm::vec3 force;
        HitBox3D hitBox;

        PhysicConstant *physicConstant;
        bool AABBIntersect(const Rigidbody& other);
    
        
    public :

        Rigidbody(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float mass, float drag, float angularDrag, bool useGravity, Shader &shader);
        ~Rigidbody() = default;

        void ApplyForce(glm::vec3 force);

        void Update(float deltaTime, std::vector<std::shared_ptr<Rigidbody>> & rigidbodies);
        
        void CollisionDetection(std::vector<std::shared_ptr<Rigidbody>> & rigidbodies);

        void ResolveCollision(Rigidbody & other);

        glm::vec3 AABBClosestPoint(const Rigidbody& other, const glm::vec3 & min , const glm::vec3 & max) {
            return glm::clamp(other.position, min, max);
        }

        


        // Setters

        void SetPosition(glm::vec3 position) {
            this->position = position;
        }

        void SetScale(glm::vec3 scale) {
            this->scale = scale;
        }

        void SetRotation(glm::vec3 rotation) {
            this->rotation = rotation;
        }

        void SetMass(float mass) {
            this->mass = mass;
        }

        void SetDrag(float drag) {
            this->drag = drag;
        }

        void SetAngularDrag(float angularDrag) {
            this->angularDrag = angularDrag;
        }

        void SetUseGravity(bool useGravity) {
            this->useGravity = useGravity;
        }

        // Getters

        glm::vec3 GetPosition() {
            return position;
        }

        glm::vec3 GetScale() {
            return scale;
        }

        glm::vec3 GetRotation() {
            return rotation;
        }

        float GetMass() {
            return mass;
        }

        float GetDrag() {
            return drag;
        }

        float GetAngularDrag() {
            return angularDrag;
        }

        bool GetUseGravity() {
            return useGravity;
        }

        // Static functions


        void ShowHitBox(glm::mat4 view, glm::mat4 projection, std::vector<glm::vec3> &validPositions) {
            hitBox.ShowHitBox(position, scale, rotation, view, projection, validPositions);
        }

};

#endif
