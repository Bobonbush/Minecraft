#ifndef ENTITY_H
#define ENTITY_H
#include "Physics/AABB.h"
#include "Physics/PhysicCons.h"
#include <vector>
#include "Block/Block.h"
#include "Algorithm.h"
#include "Texture&Shader/SoundManager.h"

class Entity
{
    protected:
        AABB box;
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 rotation;

        float head = 0.0f;
    public:
        Entity() : box(glm::vec3(0.0f, 0.0f, 0.0f)) , position(glm::vec3(0.0f)) , rotation(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)) {}
        Entity(const glm::vec3& dim) : box(dim) {}
        Entity(const glm::vec3 &pos , const glm::vec3 & rot) : box(glm::vec3(0.0f, 0.0f, 0.0f)) , position(pos) , rotation(rot), velocity(glm::vec3(0.0f)) {}

        Entity(const glm::vec3 &pos, const glm::vec3 &rot, const AABB &box) : box(box) , position(pos) , rotation(rot), velocity(glm::vec3(0.0f)) {}

        virtual void update(float deltaTime) = 0;
        virtual void FixedUpdate() = 0;

        glm::vec3 getPosition() const {
            return position;
        }

        glm::vec3 getRotation() const {
            return rotation;
        }

        glm::vec3 getVelocity() const {
            return velocity;
        }

        void setHeadPosition(float head) {
            this -> head = head;
        }

        const glm::vec3 getHeadPosition() const {
            return glm::vec3(position.x, position.y + head, position.z);
        }

        virtual void addForce(const glm::vec3 &force) = 0 ;
};

class DYNAMIC_ENTITY : public Entity {
    protected :
        glm::vec3 acceleration = glm::vec3(0.0f);
        float mass = 0.f;
        glm::vec3 force = glm::vec3(0.0f);

        float friction = 0.95f; // By default

        bool isGrounded = false;
        bool isFlying = false;

        bool UnderWater = false;
        bool Walking = false;
        bool oldWalking = false;
        bool oldGrounded = false;

        std::vector<AABB> nearBoxes;

        void applyForce() {
            acceleration += force / mass;
            force = glm::vec3(0.0f);
        }

        void resolveCollision();

        

    public :
        DYNAMIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot, const AABB &box, float mass) : Entity(pos, rot, box) , mass(mass) {}
        DYNAMIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot, float mass) : Entity(pos, rot) , mass(mass) {}
        DYNAMIC_ENTITY(float mass) : Entity() , mass(mass) {}
        DYNAMIC_ENTITY(const glm::vec3& dim) : Entity(dim) {}
        

        void addForce(const glm::vec3 &force) override;
        void ApplyGravity();

        void update(float deltaTime) override;

        void FixedUpdate() override;


        void setMass(float mass) {
            this -> mass = mass;
        }

        void setFriction(float friction) {
            this -> friction = friction;
        }

        void ApplyFriction(float friction) {
            this -> friction = friction;
        }

        void ApplyFriction() {
            this -> friction =  0.95f;  // By default
        }


        void setFlying(bool flying) {
            isFlying = flying;
        }

        bool isOnGround() {
            return isGrounded;
        }

        bool Flying() {
            return isFlying;
        }

        void addCollisioner(const std::vector<AABB> &boxe);
        bool getColliding(AABB &boxe);
        
        void isUnderWater(const bool & UnderWater) {
            this -> UnderWater = UnderWater;
        }

        const bool isUnderWater() const {
            return UnderWater;
        }

        const bool isWalking() const {
            if(Walking == oldWalking) {
                return false;
            }
            return Walking;
        }

        const bool StopWalking() const {
            return !Walking;
        }

        
        



};




#endif