#ifndef AABB_H
#define AABB_H
#include <glm/glm.hpp>
#include <iostream>

class AABB {

    protected:
    
    

    public:
    glm::vec3 position;
    const glm::vec3 dimensions;
    AABB(const glm::vec3 &data );
    void update(const glm::vec3 &data);
    glm::vec3 getVN(const glm::vec3 &normal);
    glm::vec3 getVP(const glm::vec3 &normal);
    const AABB& operator = (const AABB &box) const;
};

#endif