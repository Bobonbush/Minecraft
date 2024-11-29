#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include "ChunkBuilder.h"
#include "Renderer/RenderMaster.h"
#include "Player/player.h"
#include "WorldGenerator/Terrain.h"
#include "Algorithm.h"
#include "Maths/Frustum.h"
#include <thread>


class ChunkManager {

    struct AdjacentChunks {
        glm::vec3 up;
        glm::vec3 down;
        glm::vec3 left;
        glm::vec3 right;
        glm::vec3 front;
        glm::vec3 back;

        void update(const glm::vec3& ChunkPosition) {
            up = glm::vec3(ChunkPosition.x, ChunkPosition.y + 1, ChunkPosition.z);
            down = glm::vec3(ChunkPosition.x, ChunkPosition.y - 1, ChunkPosition.z);
            left = glm::vec3(ChunkPosition.x - 1, ChunkPosition.y, ChunkPosition.z);
            right = glm::vec3(ChunkPosition.x + 1, ChunkPosition.y, ChunkPosition.z);
            front = glm::vec3(ChunkPosition.x, ChunkPosition.y, ChunkPosition.z + 1);
            back = glm::vec3(ChunkPosition.x, ChunkPosition.y, ChunkPosition.z - 1);
        }

    };
    private:
        std::vector<ChunkSection> chunks;
        std::vector<ChunkSection> miseryChunk; // This is for the chunks that are not loaded
        RenderMaster renderMaster;
        Player* m_player;
        NoiseGenerator noise;

        float renderDistance = 12 ;
        int numLoadChunks = 2;
        bool firstRender = true;
        
        void LoadChunks();
        void UnloadChunks();
        void Recover(ChunkSection & chunk , std::vector<ChunkSection*> & adj);
        void addMiseryChunk(int x, int y, int z);
    public :

        ChunkManager();
        ~ChunkManager() = default;

        
        
        void update(const glm::mat4 &view, const glm::mat4 &projection);
        
        ChunkSection & getChunk(int x,int y, int z);
        void addChunk(int x, int y, int z);
        
        void renderChunks(const glm::mat4& view, const glm::mat4& projection);
        bool existsChunk(int x, int y, int z);

        void addBlock(float x, float y, float z, ChunkBlock block);
        void removeBlock(float x, float y, float z);
        bool existsBlock(float x, float y, float z);
        ChunkBlock getBlock(float x, float y, float z);
        glm::vec3 getBlockPosition(float x, float y, float z);
        void setBlock(int x, int y, int z, BLOCKID id);
        //void getBlock(float x , float y , float z);
        //void getChunk(float x, float z);
};

#endif // CHUNKMANAGER_H