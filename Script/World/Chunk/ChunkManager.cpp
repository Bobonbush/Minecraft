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
    chunks.clear();
}

void ChunkManager::LoadChunks() {

    auto playerPos = m_player->getPosition();
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE);

    for(int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance; x++) {
        for(int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance; z++) {
            bool chunkExists = false;
            for(auto & chunk : chunks) {
                if(chunk.getPosition().x  == x && chunk.getPosition().z == z) {
                    chunkExists = true;
                    break;
                }
            }
            if(!chunkExists) {
                addChunk(x , z );
            }
        }
    }
}