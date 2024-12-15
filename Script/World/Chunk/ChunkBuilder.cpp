#include "ChunkBuilder.h"

ChunkBuilder::ChunkBuilder(ChunkSection &chunk, const std::vector<ChunkSection*> & adj) : pChunk(&chunk), adj(adj) {
}

ChunkBuilder :: ~ChunkBuilder() {
}

void ChunkBuilder::BuildMesh(ChunkMesh & mesh) {
    pMesh = &mesh;
    AdjacentBlock directions;

    pMesh -> has_mesh = false;

    for(int y = 0 ; y <  Chunk::CHUNK_SIZE ; y++) {
        for(int x = 0 ; x < Chunk::CHUNK_SIZE ;  x++) {
            for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) { 
                glm::vec3 position = glm::vec3(x, y, z);
                ChunkBlock block = pChunk->getBlock(x, y, z);

                if(block == BLOCKID::Air) {
                    continue;
                }
                isOquaqe = false;

                pblockData = &block.getData().getBlockData();
                auto &data = *pblockData;
                directions.update(x, y, z);

                tryAddFaceToMesh(Block::Front, Block::frontNormal, data.sideCoords, position, directions.front);
                tryAddFaceToMesh(Block::Top, Block::upNormal, data.topCoords, position, directions.up);
                
                tryAddFaceToMesh(Block::Bottom, Block::downNormal, data.bottomCoords, position, directions.down);
                tryAddFaceToMesh(Block::Left, Block::leftNormal, data.sideCoords, position, directions.left);
                tryAddFaceToMesh(Block::Right, Block::rightNormal, data.sideCoords, position, directions.right);
                
                tryAddFaceToMesh(Block::Back, Block::backNormal,data.sideCoords, position, directions.back);
            }
        }
    }
}


void ChunkBuilder::tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing) {
    if(shouldMakeFace(facing, *pblockData)) {
        faceCount++;
        pMesh -> has_mesh = true;
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


void ChunkBuilder::tryAddFaceToMesh(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & normals, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing) {
    if(shouldMakeFace(facing, *pblockData)) {
        faceCount++;
        pMesh -> has_mesh = true;
        auto Coords = BlockDataBase::GetInstance() -> textureAtlas.getTexture(texCoords);
        if(vertices == Block::Right) {
            SPA::RotateArray2f(Coords, 3);
        }
        pMesh -> addFace(vertices, normals, Coords, pChunk -> getPosition(), Blockposition);
        if(vertices == Block::Right) {
            SPA::RotateArray2f(Coords, 1);
        }
    }
}

bool ChunkBuilder::shouldMakeFace(const glm::vec3 position, const BlockDataHolder & blockData) {
    auto block = pChunk -> getBlock(position.x, position.y, position.z);

    float x = position.x;
    float y = position.y;
    float z = position.z;
    //std::cout <<'\n';

    if(x < 0 ) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().x == pChunk->getPosition().x - 1) {

                if(chunk -> getBlock(Chunk::CHUNK_SIZE - 1, y, z) != BLOCKID::Air) {
                    return false;
                }

                
            }
        }
        return true;
    }

    if(x >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            
            if(chunk -> getPosition().x == pChunk->getPosition().x + 1 ) {
                
                if(chunk -> getBlock(0, y, z) != BLOCKID::Air) {
                    return false;
                }

                
            }
        }
        return true;
    }

    if(y < 0) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().y == pChunk->getPosition().y - 1) {
                if(chunk -> getBlock(x, Chunk::CHUNK_SIZE -1, z) != BLOCKID::Air) {
                    return false;
                }
            }
        }
        return true;
    }

    if(y >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().y == pChunk->getPosition().y + 1) {
                if(chunk -> getBlock(x,  0 , z) != BLOCKID::Air) {
                    return false;
                }

            }
        }
        return true;
    }

    if(z < 0) {
        for(auto & chunk : adj) {

            
            
            if(chunk -> getPosition().z == pChunk->getPosition().z - 1) {
                
                if(chunk -> getBlock(x, y,  Chunk::CHUNK_SIZE-1) != BLOCKID::Air) {
                    return false;
                }
                
            }
        }
        return true;
    }

    if(z >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            if(chunk->getPosition().z == pChunk->getPosition().z + 1) {
                if(chunk -> getBlock(x, y,  0) != BLOCKID::Air ) {
                    return false;
                }
                
            }
        }
        return true;
    }

    


    if(block == BLOCKID::Air ) {
        return true;
    }
    if(isOquaqe && block == BLOCKID::Water) {
        return false;
    }
    if(block == BLOCKID::Water) {
        return true;
    }
    return false;
}