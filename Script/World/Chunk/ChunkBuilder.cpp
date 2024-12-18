#include "ChunkBuilder.h"

ChunkBuilder::ChunkBuilder(ChunkSection &chunk, const std::vector<ChunkSection*> & adj) : pChunk(&chunk), adj(adj) {
}

ChunkBuilder :: ~ChunkBuilder() {
}

void ChunkBuilder::BuildOquaques(int x ,int y ,int z) {
    
    AdjacentBlock directions;
    directions.update(x, y, z);
    ChunkBlock block = pChunk -> getBlock(x, y, z); 
    if(y == Chunk::CHUNK_SIZE - 1  && block == BLOCKID::Air) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().y == pChunk->getPosition().y + 1) {
                if(chunk -> getBlock(x, 0, z) == BLOCKID::Water) {
                    pChunk -> setBlock(x, y, z, BLOCKID::Water);
                    block = pChunk -> getBlock(x, y, z);
                    break;
                }
            }
        }
    }

    if(block.isLiquid() ) {
        if(y -1 >= 0) {
            ChunkBlock blockBelow = pChunk -> getBlock(x, y - 1, z);
            if(blockBelow == BLOCKID::Air) {
                pChunk -> setBlock(x, y-1, z, block.getID());
               // return;
            }
        }
    }

    

    if(block == BLOCKID::Air) {
        return;
    }

    
    pblockData = &block.getData().getBlockData();
    auto &data = *pblockData;

    glm::vec3 position = glm::vec3(x, y, z);
    
    
    
    tryAddFaceToMesh(pWaterMesh, Block::Front, Block::frontNormal, data.sideCoords, position, directions.front);
    tryAddFaceToMesh(pWaterMesh, Block::Top, Block::upNormal, data.topCoords, position, directions.up);
                
    tryAddFaceToMesh(pWaterMesh, Block::Bottom, Block::downNormal, data.bottomCoords, position, directions.down);
    tryAddFaceToMesh(pWaterMesh, Block::Left, Block::leftNormal, data.sideCoords, position, directions.left);
    tryAddFaceToMesh(pWaterMesh, Block::Right, Block::rightNormal, data.sideCoords, position, directions.right);
                
    tryAddFaceToMesh(pWaterMesh, Block::Back, Block::backNormal,data.sideCoords, position, directions.back);
    
}

void ChunkBuilder::BuildMesh(ChunkMesh & mesh, ChunkMesh & waterMesh) {
    pMesh = &mesh;
    pWaterMesh = &waterMesh;
    AdjacentBlock directions;

    pMesh -> has_mesh = false;
    pWaterMesh -> has_mesh = false;

    for(int y = Chunk::CHUNK_SIZE - 1 ; y >=  0 ; y--) {
        for(int x = 0 ; x < Chunk::CHUNK_SIZE ;  x++) {
            for(int z = 0 ; z < Chunk::CHUNK_SIZE ; z++) { 
                glm::vec3 position = glm::vec3(x, y, z);
                ChunkBlock block = pChunk->getBlock(x, y, z);
                isOquaqe = false;
                if(block.isOpaque()) {
                    isOquaqe = block.isLiquid();
                    BuildOquaques(x, y, z);
                    continue;
                }
                

                pblockData = &block.getData().getBlockData();
                auto &data = *pblockData;
                directions.update(x, y, z);

                tryAddFaceToMesh(pMesh, Block::Front, Block::frontNormal, data.sideCoords, position, directions.front);
                tryAddFaceToMesh(pMesh, Block::Top, Block::upNormal, data.topCoords, position, directions.up);
                
                tryAddFaceToMesh(pMesh, Block::Bottom, Block::downNormal, data.bottomCoords, position, directions.down);
                tryAddFaceToMesh(pMesh, Block::Left, Block::leftNormal, data.sideCoords, position, directions.left);
                tryAddFaceToMesh(pMesh, Block::Right, Block::rightNormal, data.sideCoords, position, directions.right);
                
                tryAddFaceToMesh(pMesh, Block::Back, Block::backNormal,data.sideCoords, position, directions.back);
                
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


void ChunkBuilder::tryAddFaceToMesh(ChunkMesh * cMesh, const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & normals, const glm::vec2 & texCoords, const glm::vec3 Blockposition,  const glm::vec3 & facing) {
    if(shouldMakeFace(facing, *pblockData)) {
        faceCount++;
        cMesh -> has_mesh = true;
        auto Coords = BlockDataBase::GetInstance() -> textureAtlas.getTexture(texCoords);
        if(vertices == Block::Right) {
            SPA::RotateArray2f(Coords, 3);
        }
        cMesh -> addFace(vertices, normals, Coords, pChunk -> getPosition(), Blockposition);
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
                if(isOquaqe) {
                    if(chunk -> getBlock(Chunk::CHUNK_SIZE - 1, y, z).isLiquid()) {
                        return false;
                    }
                }else {

                    if(!chunk -> getBlock(Chunk::CHUNK_SIZE - 1, y, z).isOpaque()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    if(x >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            
            if(chunk -> getPosition().x == pChunk->getPosition().x + 1 ) {
                if(isOquaqe) {
                    if(chunk -> getBlock(0, y, z).isLiquid()) {
                        return false;
                    }

                    

                }else {
                    if(!chunk -> getBlock(0, y, z).isOpaque()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    if(y < 0) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().y == pChunk->getPosition().y - 1) {
                if(isOquaqe) {
                    if(chunk -> getBlock(x, Chunk::CHUNK_SIZE -1, z).isLiquid()) {
                        return false;
                    }
                }else {

                    if(!chunk -> getBlock(x, Chunk::CHUNK_SIZE -1, z).isOpaque()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    if(y >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            if(chunk -> getPosition().y == pChunk->getPosition().y + 1) {
                if(isOquaqe) {
                    if(chunk -> getBlock(x, 0, z).isLiquid()) {
                        return false;
                    }
                }else {

                    if(!chunk -> getBlock(x,  0 , z).isOpaque()) {
                        return false;
                    }
                }

            }
        }
        return true;
    }

    if(z < 0) {
        for(auto & chunk : adj) {

            
            
            if(chunk -> getPosition().z == pChunk->getPosition().z - 1) {

                if(isOquaqe) {
                    if(chunk -> getBlock(x, y,  Chunk::CHUNK_SIZE-1).isLiquid()) {
                        return false;
                    }
                }else {
                
                    if(!chunk -> getBlock(x, y,  Chunk::CHUNK_SIZE-1).isOpaque()) {
                        return false;
                    }
                }
                
            }
        }
        return true;
    }

    if(z >= Chunk::CHUNK_SIZE) {
        for(auto & chunk : adj) {
            if(chunk->getPosition().z == pChunk->getPosition().z + 1) {
                if(isOquaqe) {
                    if(chunk -> getBlock(x, y,  0).isLiquid()) {
                        return false;
                    }
                }else {
                    if(!chunk -> getBlock(x, y,  0).isOpaque() ) {
                        return false;
                    }
                }
                
            }
        }
        return true;
    }

    

    if(isOquaqe) {
        if(block.isLiquid()) {
            return false;
        }
    }
    if(block.isOpaque()) {
        return true;
    }
    return false;
}