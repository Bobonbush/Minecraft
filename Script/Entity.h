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

};

#endif