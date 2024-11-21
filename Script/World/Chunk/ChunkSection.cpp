#include "ChunkSection.h"


ChunkSection::ChunkSection(const glm::vec3 &position) : position(position) {
    for(int i = 0 ; i < Chunk::CHUNK_VOLUME ; i++) {
        blocks[i] = ChunkBlock(BLOCKID::Grass);
    }
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
    return x < 0 || y < 0 || z < 0 || x >= Chunk::CHUNK_SIZE || y >= Chunk::CHUNK_HEIGHT || z >= Chunk::CHUNK_SIZE;
}

int ChunkSection::getIndex(int x, int y, int z) const{
    //x -= position.x;
    //y -= position.y;
    //z -= position.z;
    return (x * Chunk::CHUNK_SIZE) + (y * Chunk::CHUNK_AREA) + z;
}

const glm::vec3 &ChunkSection::getPosition() const {
    return position;
}