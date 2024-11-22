#ifndef ENTITY_H
#define ENTITY_H
#include "Physics/AABB.h"

class Entity
{
    protected:
        AABB box;
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 rotation;
    public:
        Entity() : box(glm::vec3(0.0f, 0.0f, 0.0f)) , position(glm::vec3(0.0f)) , rotation(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)) {}

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

        virtual void addForce(const glm::vec3 &force) = 0 ;
};

class STATIC_ENTITY : public Entity {
    public :
        STATIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot, const AABB &box) : Entity(pos, rot, box) {}

        STATIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot) : Entity(pos, rot) {}

        STATIC_ENTITY() : Entity() {}
    
    
};

class DYNAMIC_ENTITY : public Entity {
    protected :
        glm::vec3 acceleration = glm::vec3(0.0f);
        float mass = 0.f;
        glm::vec3 force = glm::vec3(0.0f);

        float friction = 0.95f; // By default

        void applyForce() {
            acceleration += force / mass;
            force = glm::vec3(0.0f);
        }
    public :
        DYNAMIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot, const AABB &box, float mass) : Entity(pos, rot, box) , mass(mass) {}
        DYNAMIC_ENTITY(const glm::vec3 &pos, const glm::vec3 &rot, float mass) : Entity(pos, rot) , mass(mass) {}
        DYNAMIC_ENTITY(float mass) : Entity() , mass(mass) {}

        

        void addForce(const glm::vec3 &force) override {
            //velocity += force / mass;
            this -> force += force;
        }

        void update(float deltaTime) override {
        }

        void FixedUpdate() override {

            applyForce();
            velocity += acceleration;
            position += velocity;
            velocity *= friction;
            acceleration = glm::vec3(0.0f);
        }


        void setMass(float mass) {
            this -> mass = mass;
        }

        void setFriction(float friction) {
            this -> friction = friction;
        }


};




#endif