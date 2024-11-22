#include "ChunkBuilder.h"
#include "Renderer/RenderMaster.h"
#include "Player/player.h"


class ChunkManager {
    private:
        std::vector<ChunkSection> chunks;
        RenderMaster renderMaster;
        Player* m_player;

        float renderDistance = 1;
        bool FirstRender = true;
        bool existsChunk(int x, int z);
        void LoadChunks();
        void UnloadChunks();
    public :

        ChunkManager();
        ~ChunkManager() = default;

        
        
        void update();
        
        const ChunkSection & getChunk(int x, int z);
        void addChunk(int x, int z);
        void addBlock(int x, int y, int z, ChunkBlock block);
        void removeBlock(int x, int y, int z);
        void renderChunks(const glm::mat4& view, const glm::mat4& projection);
        //void getBlock(float x , float y , float z);
        //void getChunk(float x, float z);
};