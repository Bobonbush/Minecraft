#include "ChunkSection.h"


ChunkSection::ChunkSection() {
    position = glm::vec3(0.0f);
}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block) {
    if (outOfBounds(x, y, z)) {
        return;
    }
    blocks[getIndex(x, y, z)] =  block;
}

ChunkBlock ChunkSection::getBlock(int x , int y ,int z) const {
    if(outOfBounds(x, y, z)) {
        return ChunkBlock(BLOCKID::Air);
    }
    return blocks[getIndex(x, y, z)];
}

bool ChunkSection:: outOfBounds(int x , int y ,int z) {
    return x < 0 || y < 0 || z < 0 || x >= Chunk::CHUNK_SIZE || y >= Chunk::CHUNK_SIZE || z >= Chunk::CHUNK_SIZE;
}

int ChunkSection::getIndex(int x, int y, int z) {
    return x + (y * Chunk::CHUNK_SIZE) + (z * Chunk::CHUNK_AREA);
}

const glm::vec3 &ChunkSection::getPosition() const {
    return position;
}