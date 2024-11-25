#include "Frustum.h"

Frustum * Frustum::instance = nullptr;

void Frustum::update(const glm::mat4& view, const glm::mat4& projection) {
            glm::mat4 clip = projection * view;

            // right
            planes[0][0] = clip[0][3] + clip[0][0];
            planes[0][1] = clip[1][3] + clip[1][0];
            planes[0][2] = clip[2][3] + clip[2][0];
            planes[0][3] = clip[3][3] + clip[3][0];
            
            // left
            planes[1][0] = clip[0][3] - clip[0][0];
            planes[1][1] = clip[1][3] - clip[1][0];
            planes[1][2] = clip[2][3] - clip[2][0];
            planes[1][3] = clip[3][3] - clip[3][0];
            
            // bottom

            planes[2][0] = clip[0][3] + clip[0][1];
            planes[2][1] = clip[1][3] + clip[1][1];
            planes[2][2] = clip[2][3] + clip[2][1];
            planes[2][3] = clip[3][3] + clip[3][1];

            // top
            planes[3][0] = clip[0][3] - clip[0][1];
            planes[3][1] = clip[1][3] - clip[1][1];
            planes[3][2] = clip[2][3] - clip[2][1];
            planes[3][3] = clip[3][3] - clip[3][1];

            // far
            planes[4][0] = clip[0][3] - clip[0][2];
            planes[4][1] = clip[1][3] - clip[1][2];
            planes[4][2] = clip[2][3] - clip[2][2];
            planes[4][3] = clip[3][3] - clip[3][2];

            // near
            planes[5][0] = clip[0][3] + clip[0][2];
            planes[5][1] = clip[1][3] + clip[1][2];
            planes[5][2] = clip[2][3] + clip[2][2];
            planes[5][3] = clip[3][3] + clip[3][2];

            for(int i = 0 ; i < 6 ; i++) {
                float length = glm::length(glm::vec3(planes[i]));
                planes[i] /= length;
            }
}


bool Frustum::FrustumCulling(const glm::vec3 & minBox, const glm::vec3 &maxBox) {

    for(int i = 0 ; i < 6 ; i ++) {
        int out = 0;
        out += (glm::dot(planes[i], glm::vec4(minBox.x, minBox.y, minBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(maxBox.x, minBox.y, minBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(minBox.x, maxBox.y, minBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(maxBox.x, maxBox.y, minBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(minBox.x, minBox.y, maxBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(maxBox.x, minBox.y, maxBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(minBox.x, maxBox.y, maxBox.z, 1.0f)) < 0.0) ? 1 : 0;
        out += (glm::dot(planes[i], glm::vec4(maxBox.x, maxBox.y, maxBox.z, 1.0f)) < 0.0) ? 1 : 0;

        if(out == 8) {
            return true;
        }
    }

    int out = 0 ;
    return false;
}

