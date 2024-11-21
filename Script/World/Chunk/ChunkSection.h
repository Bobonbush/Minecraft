#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H
#include "Chunk.h"
#include "Block/ChunkBlock.h"
#include "ChunkMesh.h"


class ChunkSection {
    private: 
        static bool outOfBounds(int x, int y, int z);
        static int getIndex(int x, int y, int z);
        std::array<ChunkBlock, Chunk::CHUNK_VOLUME> blocks;
        
        
        glm::vec3 position;

    public :
        ChunkMesh mesh;

        ChunkSection(glm::vec3 &position);
        ChunkSection() = default;

        void setBlock(int x, int y, int z, ChunkBlock id);

        ChunkBlock getBlock(int x, int y, int z) const;

        const glm::vec3 &getPosition() const;

        void outputMesh() {
            mesh.bufferMesh();
        }
};

#endif // CHUNKSECTION_H