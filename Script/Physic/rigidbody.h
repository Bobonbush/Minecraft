#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Texture.h"
#include <memory>
#include <algorithm>
#include <set>
#include "Algorithm.h"

#include "PhysicVariable.h"




class Rigidbody { 
    private :
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

        PhysicConstant *physicConstant;

        static std::vector<std::shared_ptr<Rigidbody>> rigidbodies;         //  List of all rigidbodies
        bool AABBIntersect(const Rigidbody& other);
        static void AABBDetection();
        
    public :

        Rigidbody(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float mass, float drag, float angularDrag, bool useGravity);
        ~Rigidbody() = default;

        void ApplyForce(glm::vec3 force);

        void Update(float deltaTime);


        static void CollisionDetection() {
            AABBDetection();
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

        static void AddRigidbody(std::shared_ptr<Rigidbody> rigidbody) {
            rigidbodies.push_back(std::move(rigidbody));
        }

        static void RemoveRigidbody(std::shared_ptr<Rigidbody>& rigidbody) {
            auto it = std::remove_if(rigidbodies.begin(), rigidbodies.end(), [&rigidbody](const std::shared_ptr<Rigidbody>& r) {
                        return r.get() == rigidbody.get();
            });
            rigidbodies.erase(it, rigidbodies.end());
}

};

#endif
