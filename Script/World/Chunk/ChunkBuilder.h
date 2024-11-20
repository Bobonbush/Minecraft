#include "ChunkMesh.h"
#include "ChunkSection.h"
#include "Chunk.h"

class ChunkBuilder {
    private:
        std::unique_ptr<ChunkSection> pChunk ;
        std::unique_ptr<ChunkMesh> pMesh;
        const std::unique_ptr<BlockDataHolder> pblockData;

        void tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & texCoords, const std::vector<GLuint> & indices, const glm::vec3 & facing);
        bool shouldMakeFace(const glm::vec3 position, const BlockDataHolder & blockData);
    
    public :
        ChunkBuilder(ChunkSection &chunk);
        void BuildMesh(ChunkMesh & mesh); 
    
};