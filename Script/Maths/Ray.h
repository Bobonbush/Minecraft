#include "Camera.h"


class Ray {
    private:
        glm::vec3 ray_start;
        glm::vec3 ray_end;
        glm::vec3 ray_direction;
    public:

        Ray(const Camera &camera);
        const glm::vec3& getRayEnd() const;
        void step(float scale);
        const float getLength() const;
};