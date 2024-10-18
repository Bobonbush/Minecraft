#ifndef BLOCK_H
#define BLOCK_H
#include "Texture.h"
#include "Camera.h"

class Block {
    private:
        
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    protected: 
        CubeRenderer *cubeRenderer;
    public :

        Block(glm :: vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Block();
        virtual void Render(glm::mat4 view, glm::mat4 projection);
        void SetPosition(glm::vec3 position);
        void SetScale(glm::vec3 scale);
        void SetRotation(glm::vec3 rotation);
        glm::vec3 GetPosition();
        glm::vec3 GetScale();
        glm::vec3 GetRotation();

        virtual void Update(float deltaTime);

};


class Dirt : public Block{
    private:
        unsigned int texture;
    public:
        Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Dirt();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};

#endif




