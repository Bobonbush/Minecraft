#include "AABB.h"

AABB::AABB(const glm::vec3 &data) : dimensions(data) {
}

void AABB::update(const glm::vec3 &data) {
    position = data;
}

glm::vec3 AABB::getVN(const glm::vec3 &normal) {
    glm::vec3 res = position;
    if(normal.x > 0) {
        res.x += dimensions.x;
    }
    if(normal.y > 0) {
        res.y += dimensions.y;
    }
    if(normal.z > 0) {
        res.z += dimensions.z;
    }
    return res;
}

glm::vec3 AABB::getVP(const glm::vec3 &normal) {
    glm::vec3 res = position;
    if(normal.x < 0) {
        res.x += dimensions.x;
    }
    if(normal.y < 0) {
        res.y += dimensions.y;
    }
    if(normal.z < 0) {
        res.z += dimensions.z;
    }
    return res;
}