#include "ChunkManager.h"

ChunkManager::ChunkManager() {
    m_player = Player::GetInstance();
}


void ChunkManager::addChunk(int x, int z) {
    chunks.push_back(ChunkSection(glm::vec3(x, 0, z)));
    ChunkBuilder builder(chunks.back());
    builder.BuildMesh(chunks.back().mesh);
    chunks.back().mesh.bufferMesh();
}

void ChunkManager::addBlock(int x, int y, int z, ChunkBlock block) {
    int chunkX = x / Chunk::CHUNK_SIZE;
    int chunkZ = z / Chunk::CHUNK_SIZE;
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().z == chunkZ) {
            chunk.setBlock(x % Chunk::CHUNK_SIZE, y, z % Chunk::CHUNK_SIZE, block);
            ChunkBuilder builder(chunk);
            builder.BuildMesh(chunk.mesh);
            chunk.mesh.bufferMesh();
            return;
        }
    }
}

void ChunkManager::removeBlock(int x, int y, int z) {
    int chunkX = x / Chunk::CHUNK_SIZE;
    int chunkZ = z / Chunk::CHUNK_SIZE;
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().z == chunkZ) {
            chunk.setBlock(x % Chunk::CHUNK_SIZE, y, z % Chunk::CHUNK_SIZE, ChunkBlock(BLOCKID::Air));
            ChunkBuilder builder(chunk);
            builder.BuildMesh(chunk.mesh);
            chunk.mesh.bufferMesh();
            return;
        }
    }
}

void ChunkManager::renderChunks(const glm::mat4 &view, const glm::mat4 &projection) {
    for(auto & chunk : chunks) {
        renderMaster.drawChunk(chunk.mesh);
    }
    

    renderMaster.finishRender(view, projection);

    //std::cout << "Drawing chunk" << std::endl;
}

bool ChunkManager::existsChunk(int x, int z) {
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == x && chunk.getPosition().z == z) {
            return true;
        }
    }
    return false;
}
void ChunkManager::update() {
    LoadChunks();
}

void ChunkManager::UnloadChunks() {
    auto playerPos = m_player->getPosition();
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE);

    int lowerBoundX = playerChunkX - renderDistance;
    int lowerBoundZ = playerChunkZ - renderDistance;
    int upperBoundX = playerChunkX + renderDistance;
    int upperBoundZ = playerChunkZ + renderDistance;
    for(int i = 0 ; i <= (int) chunks.size()-1 ; i++) {
        auto & chunk = chunks[i];
        int chunkX = chunk.getPosition().x;
        int chunkZ = chunk.getPosition().z;
        if(chunkX < lowerBoundX || chunkX > upperBoundX || chunkZ < lowerBoundZ || chunkZ > upperBoundZ) {
            SPA::swap(chunks[i], chunks.back());
            chunks.pop_back();
        }
    }
}

void ChunkManager::LoadChunks() {
    UnloadChunks();
   

    auto playerPos = m_player->getPosition();
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE);

    bool stop = false;

    for(int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance && !stop; x++) {
        for(int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance && !stop; z++) {
            bool chunkExists = false;
            for(auto & chunk : chunks) {
                if(chunk.getPosition().x  == x && chunk.getPosition().z == z) {
                    chunkExists = true;
                    break;
                }
            }
            if(!chunkExists) {
                addChunk(x , z );
                stop = FirstRender;
            }
        }
    }
    FirstRender = true;
}