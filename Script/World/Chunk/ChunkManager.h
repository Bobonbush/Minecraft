#include "ChunkBuilder.h"
#include "Renderer/RenderMaster.h"
#include "Player/player.h"


class ChunkManager {
    private:
        std::vector<ChunkSection> chunks;
        RenderMaster renderMaster;
        Player m_player;

        float renderDistance = 5;
    public :
        
        void UnloadChunks();
        const ChunkSection & getChunk(int x, int z);
        void addChunk(int x, int z);
        void addBlock(int x, int y, int z, ChunkBlock block);
        void removeBlock(int x, int y, int z);
        void renderChunks();
        void getBlock(float x , float y , float z);
        void getChunk(float x , float z);
};