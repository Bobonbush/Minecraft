#include "Camera.h"


class Ray {
    private:
        glm::vec3 ray_start;
        glm::vec3 ray_end;
        glm::vec3 ray_direction;
    public:

        Ray(const Camera &camera) {
            this->ray_direction = camera.Front;
            this->ray_start = camera.Position;
            
        }

        const glm::vec3& getRayEnd() const {
            return ray_end;
        }

        void step(float scale) {
            ray_end += ray_direction * scale;
        }

        const float getLength() const {
            return glm::length(ray_end - ray_start);
        }
};