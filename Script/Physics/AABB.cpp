#include "AABB.h"

AABB::AABB(const glm::vec3 &data) : dimensions(data) {

}

void AABB::update(const glm::vec3 &data) {
    position = data;
}

glm::vec3 AABB::getVN(const glm::vec3 &normal) {
    glm::vec3 res = position;
    res.x += dimensions.x * normal.x;
    
    
    res.y += dimensions.y * normal.y;
    
    
    res.z += dimensions.z * normal.z;
    
    return res;
}

glm::vec3 AABB::getVP(const glm::vec3 &normal) {
    glm::vec3 res = position;
    res.x -= dimensions.x * normal.x;
    
    
    res.y -= dimensions.y * normal.y;
    
    res.z -= dimensions.z * normal.z;
    
    return res;
}

const AABB & AABB::operator = (const AABB &box) const {
    return box;
}