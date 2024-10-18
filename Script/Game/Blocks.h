#ifndef BLOCK_H
#define BLOCK_H
#include "Texture.h"
#include "Camera.h"
#include "Resource/TextureLoad.h"
#include <memory>


class Block {
    private:
        
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    protected: 
        TextureManager *textureManager;
        std::unique_ptr<CubeRenderer> cubeRenderer;
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


class Stone : public Block{
    private:
        unsigned int texture;
    public:
        Stone(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Stone();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};



class Water : public Block {
    private:
        unsigned int texture;
    public:
        Water(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Water();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};


class Sand : public Block {
    private:
        unsigned int texture;
    public:
        Sand(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Sand();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};

class Grass : public Block {
    private:
        unsigned int textureTop;
        unsigned int textureSide;
        unsigned int textureBottom;
    public:
        Grass(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Grass();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
};
#endif




