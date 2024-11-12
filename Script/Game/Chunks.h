#include "mapGen.h"


class Frustum {
    public: 

    glm::vec4 planes[6];

    void normalize(glm::vec4 & plane);
    void update();
    const bool isChunkInFrustum(const glm::vec3 & origin, float chunkSize);
};


class SubChunk {
    private:
        enum BlockType {
            AIR,
            WATER,
            SAND,
            DIRT,
            STONE
        };
        enum Biome {
            DESERT,
            FOREST,
            MOUNTAIN,
            PLAIN,
            SNOW
        };
        glm::vec3 origin;

        
        std::vector<std::shared_ptr<Block>> blocks;
        
        std::vector<std::vector<std::vector<BlockType>>> BlockMap;
        std::vector<std::vector<std::vector<glm::vec3>>> BlockPosMap;
        std::vector<int> banFace;
        std::vector<std::vector<std::vector<bool>>> LoadedBlocks;

        glm::vec3 iterator = glm::vec3(0.f);

        bool CompleteRender = false;
        bool ChunkLoaded = false;
        bool firstLoad = true;
        Setting * settings;
        ShaderManager * shaderManager;
        Player *player;
        BlockType GetBlockState(float x, float y, float z);

        void Culling();

        void AddBlock(BlockType blockType, glm::vec3 position);

        void GenerateChunk();

        void LoadBlock();

        
    public :
        SubChunk(glm::vec3 origin);
        ~SubChunk();
        void Render(glm::mat4 view, glm::mat4 projection);
        std::vector<std::shared_ptr<Rigidbody>> Update(float deltaTime);
        
        void LoadChunk();
        
        void ReloadChunk();  // Reload the chunk when the player moves


        const glm::vec3 GetOrigin() const {
            return origin;
        }

        const std::vector<std::shared_ptr<Block>> GetBlocks() const {
            return blocks;
        }
};


class Chunk {
    private:
        std::vector<std::shared_ptr<SubChunk>> subChunks;
        std::vector<std::shared_ptr<SubChunk>> RenderSubChunks;
        glm::vec3 origin;
    public :
        Chunk(glm::vec3 origin);
        ~Chunk();


        void Render(glm::mat4 view, glm::mat4 projection);

        std::vector<std::shared_ptr<Block>> GetBlocks();

        std::vector<std::shared_ptr<Rigidbody>> Update(float deltaTime, glm::vec3 playerPosition, float diameter, glm::mat4 ProjView);

        void LoadChunk();

        glm::vec3 GetOrigin() {
            return origin;
        }

        void ReloadChunk(); // Reload the chunk when the player moves

};