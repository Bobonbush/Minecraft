#ifndef CHUNKBUILDER_H
#define CHUNKBUILDER_H
#include "ChunkMesh.h"
#include "ChunkSection.h"
#include "Chunk.h"
#include "Algorithm.h"
class ChunkBuilder {

    struct AdjacentBlock {
        glm::vec3 up;
        glm::vec3 down;
        glm::vec3 left;
        glm::vec3 right;
        glm::vec3 front;
        glm::vec3 back;

        void update(float x , float y , float z) {
            up = glm::vec3(x, y + 1, z);
            down = glm::vec3(x, y - 1, z);
            left = glm::vec3(x - 1, y, z);
            right = glm::vec3(x + 1, y, z);
            front = glm::vec3(x, y, z + 1);
            back = glm::vec3(x, y, z - 1);
        }
    };


    private:
        ChunkSection* pChunk = nullptr;
        ChunkMesh * pMesh = nullptr;
        const BlockDataHolder* pblockData = nullptr;
        std::vector<ChunkSection*> adj;
        void tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing);
        void tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & normals, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing);
        bool shouldMakeFace(const glm::vec3 position, const BlockDataHolder & blockData);
    
    public :
        int faceCount = 0;
        
        ChunkBuilder(ChunkSection &chunk, const std::vector<ChunkSection*> & adjChunks);
        void BuildMesh(ChunkMesh & mesh); 
        ~ChunkBuilder();
    
};

#endif // CHUNKBUILDER_H