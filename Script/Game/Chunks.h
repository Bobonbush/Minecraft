#include "Resource/TextureLoad.h"
#include "Resource/ShaderLoad.h"
#include "Blocks.h"
#define DB_PERLIN_IMPL
#include "Resource/db_perlin.hpp"
#include "Player.h"

class Chunk {
    private:

        enum BlockType {
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

        void SoftNoise(std::vector<std::vector<float>> &elavationMap);

        void HardNoise(std::vector<std::vector<float>> &elavationMap);

        void SoftHeight(std::vector<std::vector<int>> & HeightMap);

        void HardHeight(std::vector<std::vector<int>> & HeightMap);

        Setting * settings;
        ShaderManager * shaderManager;
        Player *player;


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