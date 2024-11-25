#ifndef FRUSTUM_H
#define FRUSTUM_H
#include "Texture.h"
#include "Utils/Singleton.h"


class Frustum {

    private :
        glm::vec4 planes[6];

        Frustum() = default;
        static Frustum * instance;
    public :

        static Frustum * GetInstance() {
            if(instance == nullptr) {
                instance = new Frustum();
            }
            return instance;
        }

        ~Frustum() {
            delete instance;
        }
    
        void update(const glm::mat4& view, const glm::mat4& projection);
    
        bool FrustumCulling(const glm::vec3 &minBox, const glm::vec3 &maxBox);
};

#endif // FRUSTUM_H