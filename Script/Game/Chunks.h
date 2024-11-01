#include "Resource/TextureLoad.h"
#include "Resource/ShaderLoad.h"
#include "Blocks.h"
#define DB_PERLIN_IMPL
#include "Resource/db_perlin.hpp"
#include "Player.h"
#include "Algorithm.h"

class Chunk {
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


        std::vector<std::unique_ptr<Block>> blocks;
        
        std::vector<std::vector<std::vector<BlockType>>> BlockMap;
        std::vector<std::vector<std::vector<glm::vec3>>> BlockPosMap;
        std::vector<int> banFace;
        void SoftNoise(std::vector<std::vector<float>> &elavationMap);

        void HardNoise(std::vector<std::vector<float>> &elavationMap);

        void SoftHeight(std::vector<std::vector<int>> & HeightMap);

        void HardHeight(std::vector<std::vector<int>> & HeightMap);

        Setting * settings;
        ShaderManager * shaderManager;
        Player *player;
        
        BlockType GetBlockState(float x, float y, float z);

        void Culling();

        void AddBlock(BlockType blockType, glm::vec3 position);


    public :
        Chunk(glm::vec3 origin);
        ~Chunk();
        void Render(glm::mat4 view, glm::mat4 projection);
        std::vector<std::shared_ptr<Rigidbody>> Update(float deltaTime);
        void LoadChunk();
        void GenerateChunk();

        glm::vec3 GetOrigin() {
            return origin;
        }
};