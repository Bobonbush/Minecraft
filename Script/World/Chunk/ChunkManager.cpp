#include "ChunkManager.h"

ChunkManager::ChunkManager() {
    m_player = Player::GetInstance();
}


void ChunkManager::addChunk(int x,int y, int z) {
    if(y > Chunk::CHUNK_HEIGHT || y < 0) {
        return ;
    }
    chunks.push_back(ChunkSection(glm::vec3(x, y, z)));
    AdjacentChunks adj;
    adj.update(chunks.back().getPosition());
    if(existsChunk(adj.down.x , adj.down.y , adj.down.z)) {
        noise.BuildChunk(chunks.back(), &getChunk(adj.down.x , adj.down.y, adj.down.z));
    }else {
        noise.BuildChunk(chunks.back(), nullptr);
    }
    GetRidOfAdjacentChunks(chunks.back());
}

void ChunkManager::addBlock(int x, int y, int z, ChunkBlock block) {
    int chunkX = x / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE;
    int chunkZ = z / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE;
    int chunkY = y / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE;
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().z == chunkZ) {
            //chunk.setBlock(x % ( Chunk::CHUNK_SIZE *Chunk::CHUNK_SCALE), y % (Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE), z % (Chunk::CHUNK_SCALE * Chunk::CHUNK_SIZE), block);
            chunk.mesh.bufferMesh();
            return;
        }
    }

}

void ChunkManager::Recover(ChunkSection & chunk , std::vector<ChunkSection*> & adj) {
    std::vector<ChunkSection* > AdjChunks;
    AdjacentChunks directions;
    directions.update(chunk.getPosition());
    if(existsChunk(directions.left.x ,directions.left.y, directions.left.z)) {
        AdjChunks.push_back(&getChunk(directions.left.x, directions.left.y, directions.left.z));
        //Recover(getChunk(directions.left.x, directions.left.y, directions.left.z), temp);
    }

    if(existsChunk(directions.right.x , directions.right.y, directions.right.z)) {
        AdjChunks.push_back(&getChunk(directions.right.x, directions.right.y, directions.right.z)); 
        //Recover(getChunk(directions.right.x, directions.right.y, directions.right.z), temp);
    }

    if(existsChunk(directions.up.x , directions.up.y, directions.up.z)) {
        AdjChunks.push_back(&getChunk(directions.up.x, directions.up.y, directions.up.z)); 
       
        //Recover(getChunk(directions.up.x, directions.up.y, directions.up.z), temp);
    }

    if(existsChunk(directions.down.x , directions.down.y, directions.down.z)) {
        AdjChunks.push_back(&getChunk(directions.down.x, directions.down.y, directions.down.z)); 

        //Recover(getChunk(directions.down.x, directions.down.y, directions.down.z), temp);
    }

    if(existsChunk(directions.front.x , directions.front.y, directions.front.z)) {
        AdjChunks.push_back(&getChunk(directions.front.x, directions.front.y, directions.front.z)); 

        //Recover(getChunk(directions.front.x, directions.front.y, directions.front.z), temp);
    }

    if(existsChunk(directions.back.x , directions.back.y, directions.back.z)) {
        AdjChunks.push_back(&getChunk(directions.back.x, directions.back.y, directions.back.z)); 

        //Recover(getChunk(directions.back.x, directions.back.y, directions.back.z), temp);
    }
    
    
    ChunkBuilder builder(chunk, AdjChunks);
    builder.BuildMesh(chunk.mesh);
    chunk.mesh.bufferMesh();
}

void ChunkManager::GetRidOfAdjacentChunks(ChunkSection & Chunk) {
    
    AdjacentChunks directions;
    directions.update(Chunk.getPosition());
    
    std::vector<ChunkSection* > AdjChunks;
    
    
    std::vector<ChunkSection*> temp;
    temp.push_back(&Chunk);

    // Check if the chunk is at the edge of the world
    
    if(existsChunk(directions.left.x ,directions.left.y, directions.left.z)) {
        AdjChunks.push_back(&getChunk(directions.left.x, directions.left.y, directions.left.z));
        Recover(getChunk(directions.left.x, directions.left.y, directions.left.z), temp);
    }

    if(existsChunk(directions.right.x , directions.right.y, directions.right.z)) {
        AdjChunks.push_back(&getChunk(directions.right.x, directions.right.y, directions.right.z)); 
        Recover(getChunk(directions.right.x, directions.right.y, directions.right.z), temp);
    }

    if(existsChunk(directions.up.x , directions.up.y, directions.up.z)) {
        AdjChunks.push_back(&getChunk(directions.up.x, directions.up.y, directions.up.z)); 
       
        Recover(getChunk(directions.up.x, directions.up.y, directions.up.z), temp);
    }

    if(existsChunk(directions.down.x , directions.down.y, directions.down.z)) {
        AdjChunks.push_back(&getChunk(directions.down.x, directions.down.y, directions.down.z)); 

        Recover(getChunk(directions.down.x, directions.down.y, directions.down.z), temp);
    }

    if(existsChunk(directions.front.x , directions.front.y, directions.front.z)) {
        AdjChunks.push_back(&getChunk(directions.front.x, directions.front.y, directions.front.z)); 

        Recover(getChunk(directions.front.x, directions.front.y, directions.front.z), temp);
    }

    if(existsChunk(directions.back.x , directions.back.y, directions.back.z)) {
        AdjChunks.push_back(&getChunk(directions.back.x, directions.back.y, directions.back.z)); 

        Recover(getChunk(directions.back.x, directions.back.y, directions.back.z), temp);
    }
    
    
    
    
    ChunkBuilder builder(Chunk, AdjChunks);
    builder.BuildMesh(Chunk.mesh);
    Chunk.mesh.bufferMesh();
}

void ChunkManager::removeBlock(int x, int y, int z) {
    int chunkX = x / Chunk::CHUNK_SIZE;
    int chunkZ = z / Chunk::CHUNK_SIZE;
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().z == chunkZ) {
            chunk.setBlock(x % Chunk::CHUNK_SIZE, y, z % Chunk::CHUNK_SIZE, ChunkBlock(BLOCKID::Air));
            ChunkBuilder builder(chunk, std::vector<ChunkSection*>());
            builder.BuildMesh(chunk.mesh);
            chunk.mesh.bufferMesh();
            return;
        }
    }
}

void ChunkManager::renderChunks(const glm::mat4 &view, const glm::mat4 &projection) {
    Frustum * frustum = Frustum::GetInstance();
    int actualNumber = 0;
    int renderNumber = 0;
    for(auto & chunk : chunks) {
        const glm::vec3 minBox = glm::vec3(chunk.getPosition().x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunk.getPosition().y * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunk.getPosition().z * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
        const glm::vec3 maxBox = minBox + glm::vec3(Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
        actualNumber++;
        if(frustum->FrustumCulling(minBox, maxBox)) {
            continue;
        }
        renderNumber++;
        renderMaster.drawChunk(chunk.mesh);
    }
    std::cout << "Actual Number of Chunks: " << actualNumber << std::endl;
    std::cout << "Rendered Number of Chunks: " << renderNumber << std::endl;
    

    renderMaster.finishRender(view, projection);

    //std::cout << "Drawing chunk" << std::endl;
}

bool ChunkManager::existsChunk(int x,int y, int z) {
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == x && chunk.getPosition().y == y && chunk.getPosition().z == z) {
            return true;
        }
    }
    return false;
}
void ChunkManager::update(const glm::mat4 & view, const glm::mat4 &projection) {
    LoadChunks();

}

void ChunkManager::UnloadChunks() {
    auto playerPos = m_player->getPosition();
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE);
    int PlayerChunkY = (int) (playerPos.y / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE );

    int lowerBoundX = playerChunkX - renderDistance;
    int lowerBoundZ = playerChunkZ - renderDistance;
    int upperBoundX = playerChunkX + renderDistance;
    int upperBoundZ = playerChunkZ + renderDistance;
    int upperBoundY = PlayerChunkY + renderDistance;
    int lowerBoundY = PlayerChunkY - renderDistance;

    
    for(int i = 0 ; i <= (int) chunks.size()-1 ; i++) {
        auto & chunk = chunks[i];
        int chunkX = chunk.getPosition().x;
        int chunkZ = chunk.getPosition().z;
        int chunkY = chunk.getPosition().y;
        if(chunkX < lowerBoundX || chunkX > upperBoundX || chunkZ < lowerBoundZ || chunkZ > upperBoundZ) {
            SPA::swap(chunks[i], chunks.back());
            chunks.pop_back();
        }
        if(chunkY < lowerBoundY || chunkY > upperBoundY) {
            SPA::swap(chunks[i], chunks.back());
            chunks.pop_back();
        }
    }
}



void ChunkManager::LoadChunks() {
    UnloadChunks();
   

    auto playerPos = m_player->getPosition();
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE);
    int playerChunkY = (int) (playerPos.y / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE);

    std::vector<glm::vec3> validPosition;
    Frustum * frustum = Frustum::GetInstance();
    for(int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance ; x++) {
        
        for(int y = SPA::max(playerChunkY - renderDistance, 0.0f); y < SPA::min( playerChunkY + renderDistance, 1.0f * Chunk::CHUNK_HEIGHT); y++) {
            
            for(int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance ; z++) {
                bool chunkExists = false;

                const glm::vec3 minBox = glm::vec3(x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, y * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, z * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
                const glm::vec3 maxBox = minBox + glm::vec3(Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
                
                if(frustum->FrustumCulling(minBox, maxBox)) {
                    continue;
                }
                for(auto & chunk : chunks) {
                    if(chunk.getPosition().x  == x && chunk.getPosition().y == y &&chunk.getPosition().z == z) {
                        chunkExists = true;
                        break;
                    }
                }
                if(!chunkExists) {
                    validPosition.push_back(glm::vec3(x, y, z));
                }
            }
        }
    }

    std::sort(validPosition.begin(), validPosition.end(), [&](const glm::vec3 & a, const glm::vec3 & b) {
        /*
        if(a.y != b.y && SPA::abs(a.y - playerChunkY) != SPA::abs(b.y - playerChunkY)) {
            return SPA::abs(a.y - playerChunkY) > SPA::abs(b.y - playerChunkY);
        }
        */
        return glm::distance(glm::vec3(playerChunkX, playerChunkY, playerChunkZ), a) + SPA::abs(playerChunkY - a.y) > glm::distance(glm::vec3(playerChunkX, playerChunkY, playerChunkZ), b) + SPA::abs(playerChunkY - b.y);
    });

    int cnt = 0;
    
    while(!validPosition.empty() && cnt <= numLoadChunks) {
        addChunk(validPosition.back().x, validPosition.back().y, validPosition.back().z);
        validPosition.pop_back();
        cnt++;
    }
}

ChunkSection& ChunkManager::getChunk(int x, int y, int z) {
    int chunkX = x ;
    int chunkZ = z ;
    int chunkY = y ;
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().y == chunkY &&  chunk.getPosition().z == chunkZ) {
            return chunk;
        }
    }
    std::cout << "Chunk not found" << std::endl;
    return chunks[0];
}