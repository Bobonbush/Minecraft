#ifndef HANDMODEL_H
#define HANDMODEL_H
#include "Model.h"
#include <iostream>
#include "Texture.h"
#include "Texture&Shader/TextureAtlas.h"
#include "Block/BlockDataBase.h"
#include "Block/Block.h"
#include "Texture&Shader/ShaderManager.h"
#include "Config.h"

class HandModel {
    private:
        float cooldown = 0.0f;
        

    protected :
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 defaultPosition;
        glm::vec3 defaultRotation;
        glm::vec3 scale;
        std::unique_ptr<Model> model;

        glm::vec3 destinationPosition;
        glm::vec3 destinationRotation;

        float rotationSpeed = 580.5f;
        float movementSpeed = 1.5f;

        bool Hit = false;
        bool ContinuosHit = false;

        std::shared_ptr<Shader> shader;
    public :
        HandModel( const glm::vec3 & scale);
        ~HandModel() = default;
        virtual void render(const glm::mat4 & view, const glm::mat4 &projection) = 0;
        virtual void update(const float & deltaTime) = 0;

        void setCooldown(float time);

        void addData(const Mesh & mesh);
        virtual void addData(const BLOCKID & id) = 0;

        void BeingHit();
        void BeingContinuosHit();
        void StopContinuosHit();

        virtual int getID()  = 0;

        
};


#endif // HANDMODEL_H

