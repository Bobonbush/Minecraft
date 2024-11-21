#include "ChunkBuilder.h"

ChunkBuilder::ChunkBuilder(ChunkSection &chunk) : pChunk(&chunk) {
}

ChunkBuilder :: ~ChunkBuilder() {
}

void ChunkBuilder::BuildMesh(ChunkMesh & mesh) {
    pMesh = &mesh;
    AdjacentBlock directions;

    for(int y = 0 ; y <  Chunk::CHUNK_HEIGHT ; y++) {
        for(int x = 0 ; x < Chunk::CHUNK_SIZE ;  x++) {
            for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) { 
                glm::vec3 position = glm::vec3(x, y, z);
                ChunkBlock block = pChunk->getBlock(x, y, z);

                if(block == BLOCKID::Air) {
                    continue;
                }

                pblockData = &block.getData().getBlockData();
                auto &data = *pblockData;
                directions.update(x, y, z);
                tryAddFaceToMesh(Block::Front, data.sideCoords, position, directions.front);
                tryAddFaceToMesh(Block::Top, data.topCoords, position, directions.up);
                
                tryAddFaceToMesh(Block::Bottom, data.bottomCoords, position, directions.down);
                tryAddFaceToMesh(Block::Left, data.sideCoords, position, directions.left);
                tryAddFaceToMesh(Block::Right, data.sideCoords, position, directions.right);
                
                tryAddFaceToMesh(Block::Back, data.sideCoords, position, directions.back);
            }
        }
    }
}

void ChunkBuilder::tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing) {
    if(shouldMakeFace(facing, *pblockData)) {
        faceCount++;
        
        auto Coords = BlockDataBase::GetInstance() -> textureAtlas.getTexture(texCoords);
        if(vertices == Block::Right) {
            SPA::RotateArray2f(Coords, 3);
        }
        pMesh -> addFace(vertices, Coords, pChunk -> getPosition(), Blockposition);
        if(vertices == Block::Right) {
            SPA::RotateArray2f(Coords, 1);
        }
    }
}

bool ChunkBuilder::shouldMakeFace(const glm::vec3 position, const BlockDataHolder & blockData) {
    auto block = pChunk -> getBlock(position.x, position.y, position.z);

   
    if(block == BLOCKID::Air) {
        return true;
    }
    else {
        return false;
    }
}