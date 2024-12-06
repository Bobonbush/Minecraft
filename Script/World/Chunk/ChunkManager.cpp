#include "ChunkManager.h"

ChunkManager::ChunkManager() {
    m_player = Player::GetInstance();
}

void ChunkManager::addMiseryChunk(int x, int y, int z) {
    if(y >= Chunk::CHUNK_HEIGHT || y < 0) {
        return ;
    }
    miseryChunk.push_back(ChunkSection(glm::vec3(x, y, z)));
    noise.BuildChunk(miseryChunk.back(), nullptr);
}


void ChunkManager::addChunk(int x,int y, int z) {
    if(y >= Chunk::CHUNK_HEIGHT || y < 0) {
        return ;
    }

    if(chunkMap.find(HashFunction(x, y, z)) != chunkMap.end()) {
        chunks.push_back(chunkMap[HashFunction(x, y, z)]);
        return ;
    }

    chunks.push_back(ChunkSection(glm::vec3(x, y, z)));
    AdjacentChunks adj;
    adj.update(chunks.back().getPosition());
    if(!existsChunk(adj.down.x , adj.down.y , adj.down.z)) {
        addMiseryChunk(adj.down.x, adj.down.y, adj.down.z);
    }


    if(existsChunk(adj.down.x , adj.down.y , adj.down.z)) {
        noise.BuildChunk(chunks.back(), &getChunk(adj.down.x , adj.down.y, adj.down.z));
    }else {

        noise.BuildChunk(chunks.back(), nullptr);
    }
    Recover(chunks.back(), std::vector<ChunkSection*>());

}



void ChunkManager::Recover(ChunkSection & chunk , std::vector<ChunkSection*> & adj) {
    std::vector<ChunkSection* > AdjChunks;
    AdjacentChunks directions;
    directions.update(chunk.getPosition());
    
    if(!existsChunk(directions.left.x ,directions.left.y, directions.left.z)) {
        addMiseryChunk(directions.left.x, directions.left.y, directions.left.z);
    }
    if(existsChunk(directions.left.x , directions.left.y, directions.left.z))
        AdjChunks.push_back(&getChunk(directions.left.x, directions.left.y, directions.left.z));

    if(!existsChunk(directions.right.x , directions.right.y, directions.right.z)) {
        addMiseryChunk(directions.right.x, directions.right.y, directions.right.z);
    }
    if(existsChunk(directions.right.x , directions.right.y, directions.right.z))
        AdjChunks.push_back(&getChunk(directions.right.x, directions.right.y, directions.right.z)); 
       

    if(!existsChunk(directions.up.x , directions.up.y, directions.up.z)) {
        addMiseryChunk(directions.up.x, directions.up.y, directions.up.z);
    }
    if(existsChunk(directions.up.x , directions.up.y, directions.up.z))
        AdjChunks.push_back(&getChunk(directions.up.x, directions.up.y, directions.up.z)); 
       

    if(!existsChunk(directions.down.x , directions.down.y, directions.down.z)) {
        addMiseryChunk(directions.down.x, directions.down.y, directions.down.z);
        
    }
    if(existsChunk(directions.down.x , directions.down.y, directions.down.z))
        AdjChunks.push_back(&getChunk(directions.down.x, directions.down.y, directions.down.z)); 


    if(!existsChunk(directions.front.x , directions.front.y, directions.front.z)) {
        addMiseryChunk(directions.front.x, directions.front.y, directions.front.z);
        
    }
    if(existsChunk(directions.front.x , directions.front.y, directions.front.z))
        AdjChunks.push_back(&getChunk(directions.front.x, directions.front.y, directions.front.z)); 


    if(!existsChunk(directions.back.x , directions.back.y, directions.back.z)) {
        addMiseryChunk(directions.back.x, directions.back.y, directions.back.z);
    }
    if(existsChunk(directions.back.x , directions.back.y, directions.back.z))
        AdjChunks.push_back(&getChunk(directions.back.x, directions.back.y, directions.back.z)); 
    
    
    
    ChunkBuilder builder(chunk, AdjChunks);
    builder.BuildMesh(chunk.mesh);
    chunk.mesh.bufferMesh();
}



void ChunkManager::renderChunks(const glm::mat4 &view, const glm::mat4 &projection) {
    Frustum * frustum = Frustum::GetInstance();
    int actualNumber = 0;
    int renderNumber = 0;
    for(auto & chunk : chunks) {
        const glm::vec3 minBox = glm::vec3(chunk.getPosition().x * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunk.getPosition().y * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunk.getPosition().z * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
        const glm::vec3 maxBox = minBox + glm::vec3(Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);
        
        if(chunk.mesh.has_mesh == false) {
            continue;
        } 
    
        if(frustum->FrustumCulling(minBox, maxBox)) {
            continue;
        }

        
        renderMaster.drawChunk(chunk.mesh);
    }


    renderMaster.finishRender(view, projection);

    //std::cout << "Drawing chunk" << std::endl;
}

bool ChunkManager::existsChunk(int x,int y, int z) {
    for(auto & chunk : chunks) {
        if(chunk.getPosition().x == x && chunk.getPosition().y == y && chunk.getPosition().z == z) {
            return true;
        }
    }

    for(auto & chunk : miseryChunk) {
        if(chunk.getPosition().x == x && chunk.getPosition().y == y && chunk.getPosition().z == z) {
            return true;
        }
    }
    return false;
}

void ChunkManager::addBlock(float x, float y, float z, ChunkBlock block) {
    x += Chunk::CHUNK_SCALE / 2.f;
    y += Chunk::CHUNK_SCALE / 2.f;
    z += Chunk::CHUNK_SCALE / 2.f;
    int chunkX = x / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE - (x < 0);
    int chunkZ = z / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE - (z < 0);
    int chunkY = y / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE - (y < 0);

    if(!existsChunk(chunkX, chunkY, chunkZ)) {
        std::cout << "WTF" << '\n';
        return ;
    }

    ChunkSection & chunk = getChunk(chunkX, chunkY, chunkZ);
    x -= chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ; 
    y -= chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    z -= chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    chunk.setBlock(x, y, z, block);

    x = (int)x;
    y = (int)y;
    z = (int)z;

    Recover(chunk, std::vector<ChunkSection*>());
    if(x == 0 ) {
        if(existsChunk(chunkX - 1, chunkY, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX - 1, chunkY, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }
    if(x == 15) {
        if(existsChunk(chunkX + 1, chunkY, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX + 1, chunkY, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(y == 0) {
        if(existsChunk(chunkX, chunkY - 1, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX, chunkY - 1, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(y == 15) {
        if(existsChunk(chunkX, chunkY + 1, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX, chunkY + 1, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(z == 0) {
        if(existsChunk(chunkX, chunkY, chunkZ - 1)) {
            ChunkSection & adj = getChunk(chunkX, chunkY, chunkZ - 1);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(z == 15) {
        if(existsChunk(chunkX, chunkY, chunkZ + 1)) {
            ChunkSection & adj = getChunk(chunkX, chunkY, chunkZ + 1);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }


}


bool ChunkManager::existsBlock(float x ,float y ,float z) {
    x +=  Chunk::CHUNK_SCALE / 2.f;
    y+= Chunk::CHUNK_SCALE / 2.f;
    z +=  Chunk::CHUNK_SCALE / 2.f;
    int chunkX = x / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (x < 0);
    int chunkZ = z / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (z < 0);
    int chunkY = y / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (y < 0);
    
    if(!existsChunk(chunkX, chunkY, chunkZ)) {
        return false;
    }
    ChunkSection & chunk = getChunk(chunkX, chunkY, chunkZ);
    x -= chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ; 
    y -= chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    z -= chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    //x -= negX;
    //y -= negY;
    //z -= negZ;
    return chunk.getBlock(x, y, z).getID() != BLOCKID::Air;
}

void ChunkManager::removeBlock(float x, float y, float z) {
    x += Chunk::CHUNK_SCALE /2.f;
    y += Chunk::CHUNK_SCALE /2.f;
    z += Chunk::CHUNK_SCALE /2.f;
    int chunkX = x / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (x < 0);
    int chunkZ = z / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (z < 0);
    int chunkY = y / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (y < 0);
    if(!existsChunk(chunkX, chunkY, chunkZ)) {
        std::cout << "???" << '\n';
        return ;
    }

    x -= chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ; 
    y -= chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    z -= chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;

    ChunkSection & chunk = getChunk(chunkX, chunkY, chunkZ);
    chunk.setBlock(x, y, z, BLOCKID::Air);

    x = (int)x;
    y = (int)y;
    z = (int)z;

    Recover(chunk, std::vector<ChunkSection*>());
    if(x == 0 ) {
        if(existsChunk(chunkX - 1, chunkY, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX - 1, chunkY, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }
    if(x == 15) {
        if(existsChunk(chunkX + 1, chunkY, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX + 1, chunkY, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(y == 0) {
        if(existsChunk(chunkX, chunkY - 1, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX, chunkY - 1, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(y == 15) {
        if(existsChunk(chunkX, chunkY + 1, chunkZ)) {
            ChunkSection & adj = getChunk(chunkX, chunkY + 1, chunkZ);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(z == 0) {
        if(existsChunk(chunkX, chunkY, chunkZ - 1)) {
            ChunkSection & adj = getChunk(chunkX, chunkY, chunkZ - 1);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }

    if(z == 15) {
        if(existsChunk(chunkX, chunkY, chunkZ + 1)) {
            ChunkSection & adj = getChunk(chunkX, chunkY, chunkZ + 1);
            Recover(adj, std::vector<ChunkSection*>());
        }
    }
}
void ChunkManager::update(const glm::mat4 & view, const glm::mat4 &projection) {
    LoadChunks();
    miseryChunk.clear();
}

ChunkBlock ChunkManager::getBlock(float x, float y, float z) {
    x += Chunk::CHUNK_SCALE / 2.f;
    y += Chunk::CHUNK_SCALE / 2.f;
    z += Chunk::CHUNK_SCALE / 2.f;
    int chunkX = x / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (x < 0) ;
    int chunkZ = z / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (z < 0) ;
    int chunkY = y / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (y < 0) ;
    if(!existsChunk(chunkX, chunkY, chunkZ)) {
        return BLOCKID::Air;
    }
    ChunkSection & chunk = getChunk(chunkX, chunkY, chunkZ);
    x -= chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE;
    y -= chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE ;
    z -= chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE;

    if(x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15) {
        std::cout << "CLGT" << '\n';
        //return BLOCKID::Air;
    }
    

    //x -= negX;
    //y -= negY;
    //z -= negZ;
    return chunk.getBlock(x, y, z);
}

glm::vec3 ChunkManager::getBlockPosition(float x , float y , float z) {
    x += Chunk::CHUNK_SCALE / 2.f;
    y += Chunk::CHUNK_SCALE / 2.f;
    z += Chunk::CHUNK_SCALE / 2.f;
    int chunkX = x / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (x < 0);
    int chunkZ = z / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (z < 0);
    int chunkY = y / Chunk::CHUNK_SIZE / Chunk::CHUNK_SCALE - (y < 0);
    if(!existsChunk(chunkX, chunkY, chunkZ)) {
        return glm::vec3(0, 0, 0);
    }


    
    glm::vec3 TruthPosition = glm::vec3(chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE, chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE);

    x -= chunkX * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE;
    y -= chunkY * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE;
    z -= chunkZ * Chunk::CHUNK_SIZE * Chunk::CHUNK_SCALE;
    x = (int)x;
    y = (int)y ;
    z = (int)z;
    return glm::vec3(TruthPosition.x + x , TruthPosition.y + y , TruthPosition.z + z);
}

void ChunkManager::UnloadChunks() {
    auto playerPos = m_player->getPosition();
    playerPos.x += Chunk::CHUNK_SCALE / 2.f;
    playerPos.y += Chunk::CHUNK_SCALE / 2.f;
    playerPos.z += Chunk::CHUNK_SCALE / 2.f; 
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE) - (playerPos.x < 0);
    int PlayerChunkY = (int) (playerPos.y / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE) - (playerPos.y < 0);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE /Chunk::CHUNK_SCALE ) - (playerPos.z < 0);

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
            chunkMap[HashFunction(chunkX, chunkY, chunkZ)] = chunks.back();
            chunks.pop_back();
        }
    }
}



void ChunkManager::LoadChunks() {
    UnloadChunks();
   

    auto playerPos = m_player->getPosition();
    
    playerPos.x += Chunk::CHUNK_SCALE / 2.f;
    playerPos.y += Chunk::CHUNK_SCALE / 2.f;
    playerPos.z += Chunk::CHUNK_SCALE / 2.f;
    int playerChunkX = (int) (playerPos.x / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE) - (playerPos.x < 0);
    int playerChunkY = (int) (playerPos.y / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE) - (playerPos.y < 0);
    int playerChunkZ = (int) (playerPos.z / Chunk::CHUNK_SIZE/Chunk::CHUNK_SCALE) - (playerPos.z < 0);
    

    std::vector<glm::vec3> validPosition;
    Frustum * frustum = Frustum::GetInstance();
    for(int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance ; x++) {
        
        for(int y = SPA::max(playerChunkY - renderDistance/ 2.f, 0.0f); y < SPA::min( playerChunkY + renderDistance/2.f, 1.0f * Chunk::CHUNK_HEIGHT); y++) {
            
            for(int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance ; z++) {
                bool chunkExists = false;
                if(glm::distance(glm::vec3(playerChunkX, 0, playerChunkZ), glm::vec3(x, 0, z)) > renderDistance) {
                    continue;
                }

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
    
    while(!validPosition.empty() && cnt < numLoadChunks) {
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

    for(auto & chunk : miseryChunk) {
        if(chunk.getPosition().x == chunkX && chunk.getPosition().y == chunkY &&  chunk.getPosition().z == chunkZ) {
            return chunk;
        }
    }
    std::cout << "NGU"<<'\n';
    return chunks[0];
}

long long ChunkManager::HashFunction(int x ,int y ,int z) {
    return (long long)x * 73856093 ^ (long long)y * 19349663 ^ (long long)z * 83492791;
}