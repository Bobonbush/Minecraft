#ifndef CHUNKMESH_H
#define CHUNKMESH_H
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Chunk.h"
class ChunkMesh {
    private:
        
        Model Chunkmodel;
        Mesh mesh;
        GLuint indexIndex = 0;
        
    
    public :
        bool has_mesh = false;
        ChunkMesh();
        void addFace(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & texCoords, const glm::vec3 & position, const glm::vec3 & blockPosition);
        const Model & getModel() const;

        void bufferMesh();
};

#endif // CHUNKMESH_H