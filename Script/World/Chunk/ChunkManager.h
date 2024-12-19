#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include "ChunkBuilder.h"
#include "Renderer/RenderMaster.h"
#include "Player/player.h"
#include "WorldGenerator/Terrain.h"
#include "Algorithm.h"
#include "Maths/Frustum.h"
#include <thread>
#include <map>


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

    struct EightFaceAdjacentChunks {
        std::vector<glm::vec3> allPosition;

        void update(const glm::vec3 & ChunkPosition) {
            allPosition.clear();
            for(int x = -1 ; x <= 1 ; x++) {
                for(int y = -1 ; y <= 1 ; y++) {
                    for(int z = -1 ; z <= 1 ; z++) {
                        if(x == 0 && y == 0 && z == 0) {
                            continue;
                        }
                        allPosition.push_back(glm::vec3(ChunkPosition.x + x, ChunkPosition.y + y, ChunkPosition.z + z));
                    }
                }
            }
        }
    };
    private:
        std::vector<ChunkSection> chunks;
        std::vector<ChunkSection> miseryChunk; // This is for the chunks that are not loaded
        RenderMaster renderMaster;
        Player* m_player;
        NoiseGenerator noise;

        struct Vec3Comparator {
            bool operator()(const glm::vec3& lhs, const glm::vec3& rhs) const {
                if (lhs.x != rhs.x) return lhs.x < rhs.x;
                if (lhs.y != rhs.y) return lhs.y < rhs.y;
                return lhs.z < rhs.z;
            }
};


        std::map<glm::vec3 , std::array<ChunkBlock, Chunk::CHUNK_VOLUME>, Vec3Comparator> chunkMap;
        std::map<glm::vec3 , bool, Vec3Comparator> isMisery;
        float renderDistance = 12;
        int numLoadChunks = 1;
        bool firstRender = true;
        
        void LoadChunks();
        void UnloadChunks();
        void Recover(ChunkSection & chunk , std::vector<ChunkSection*> & adj);
        void addMiseryChunk(int x, int y, int z);
    public :

        ChunkManager();
        ~ChunkManager() = default;

        glm::vec3 HashFunction(int x ,int y ,int z);

        
        
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

        void ReBuildChunk(int x, int y, int z);

        //void getBlock(float x , float y , float z);
        //void getChunk(float x, float z);
};

#endif // CHUNKMANAGER_H