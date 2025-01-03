#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H
#include "Chunk.h"
#include "Block/ChunkBlock.h"
#include "ChunkMesh.h"
#include "Algorithm.h"


class ChunkSection {
    private: 
        static bool outOfBounds(int x, int y, int z);
        int getIndex(int x, int y, int z) const;
        std::array<ChunkBlock, Chunk::CHUNK_VOLUME> blocks;
        
        glm::vec3 position;
        bool Changed = false;

    public :
        ChunkMesh mesh;
        ChunkMesh waterMesh;

        ChunkSection(const glm::vec3& position);
        ChunkSection() = default;

        void setBlock(int x, int y, int z, ChunkBlock id);

        ChunkBlock getBlock(int x, int y, int z) const;

        const glm::vec3 &getPosition() const;

        glm::vec3 toWorldPosition(int x , int y ,int z);

        std::array<ChunkBlock, Chunk::CHUNK_VOLUME> & getBlocks() {
            return blocks;
        }

        void setBlocks(const std::array<ChunkBlock, Chunk::CHUNK_VOLUME> & _blocks) {
            blocks = _blocks;
        }


        void setChanged(bool changed) {
            
            Changed = changed;
        }

        bool isChanged() {
            bool temp = Changed;
            Changed = false;
            return temp;
        }
};

#endif // CHUNKSECTION_H