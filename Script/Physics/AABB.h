#ifndef AABB_H
#define AABB_H
#include <glm/glm.hpp>

class AABB {

    protected:
    glm::vec3 position;
    const glm::vec3 dimensions;

    public:
    AABB(const glm::vec3 &data );
    void update(const glm::vec3 &data);
    glm::vec3 getVN(const glm::vec3 &normal);
    glm::vec3 getVP(const glm::vec3 &normal);
};

#endif