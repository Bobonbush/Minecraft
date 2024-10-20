#ifndef BLOCK_H
#define BLOCK_H
#include "Texture.h"
#include "Camera.h"
#include "Resource/TextureLoad.h"
#include <memory>

class HitBox3D {
    private:
        static std::unique_ptr<CubeRenderer> cubeRenderer;
    public : 
        HitBox3D(Shader &shader);
        ~HitBox3D();
        void ShowHitBox(glm::mat4 view, glm::mat4 projection , glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, std::vector<glm::vec3> &validPositions);
    
};


class Block {
    private:
        
        
    protected: 
        std::unique_ptr<HitBox3D> Box;
        TextureManager *textureManager;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    public :

        Block(glm :: vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Block();
        void SetPosition(glm::vec3 position);
        void SetScale(glm::vec3 scale);
        void SetRotation(glm::vec3 rotation);
        glm::vec3 GetPosition();
        glm::vec3 GetScale();
        glm::vec3 GetRotation();

        virtual void PrepareRender(Frustum frustum);
        virtual void Render(glm::mat4 view, glm::mat4 projection);
        virtual void Update(float deltaTime);
        

        bool FrustumCulling(Frustum frustum);

};





class Dirt : public Block{
    private:
        unsigned int texture;
        static std::unique_ptr<CubeRenderer> cubeRenderer;
        static std::vector<glm::vec3> validPositions;
    public:
        Dirt(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Dirt();

        void Render(glm::mat4 view, glm::mat4 projection);
        void PrepareRender(Frustum frustum);
        void Update(float deltaTime);
};


class Stone : public Block {
    private:
        unsigned int texture;
        static std::unique_ptr<CubeRenderer> cubeRenderer;
        static std::vector<glm::vec3> validPositions;
    public:
        Stone(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Stone();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
        void PrepareRender(Frustum frustum);
};



class Water : public Block {
    private:
        unsigned int texture;
        static std::unique_ptr<CubeRenderer> cubeRenderer;
        static std::vector<glm::vec3> validPositions;
    public:
        Water(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Water();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
        void PrepareRender(Frustum frustum);
};


class Sand : public Block {
    private:
        unsigned int texture;
        static std::unique_ptr<CubeRenderer> cubeRenderer;

        static std::vector<glm::vec3> validPositions;
    public:
        Sand(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Sand();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
        void PrepareRender(Frustum frustum);
};

class Grass : public Block {
    private:
        unsigned int textureTop;
        unsigned int textureSide;
        unsigned int textureBottom;
        static std::unique_ptr<CubeRenderer> cubeRenderer;

        static std::vector<glm::vec3> validPositions;
    public:
        Grass(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Shader &shader);
        ~Grass();

        void Render(glm::mat4 view, glm::mat4 projection);
        void Update(float deltaTime);
        void PrepareRender(Frustum frustum);
};

#endif




