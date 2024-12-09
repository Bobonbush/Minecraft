#include "Ray.h"

Ray::Ray(const Camera &camera) {
    this->ray_direction = glm::normalize(camera.Front);
    this->ray_start = camera.Position;
    this-> ray_end = camera.Position;     
}

const glm::vec3& Ray::getRayEnd() const {
    return ray_end;
}

void Ray::step(float scale) {
    ray_end += ray_direction * scale;
}

const float Ray::getLength() const {
    return glm::length(ray_end - ray_start);
}

