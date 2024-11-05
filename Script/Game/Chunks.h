#include "Resource/TextureLoad.h"
#include "Resource/ShaderLoad.h"
#include "Blocks.h"
#define DB_PERLIN_IMPL
#include "Resource/db_perlin.hpp"
#include "Player.h"
#include "Algorithm.h"


struct Frustum {
    glm::vec4 planes[6];

    void normalize(glm::vec4 & plane) {
        float distance = glm::length(glm::vec3(plane));
        plane /= distance;

        return ;
    }



    void update() {
        Player * player = Player::getInstance();
        Setting * settings = Setting::getInstance();
        glm::mat4 view = player -> getViewMatrix();
        glm::mat4 projection = player -> getProjectionMatrix(settings -> getResolution().x , settings -> getResolution().y);
        glm::mat4 viewProjMatrix =  projection * view ;
        
        planes[0].x = viewProjMatrix[0][3] + viewProjMatrix[0][0];
        planes[0].y = viewProjMatrix[1][3] + viewProjMatrix[1][0];
        planes[0].z = viewProjMatrix[2][3] + viewProjMatrix[2][0];
        planes[0].w = viewProjMatrix[3][3] + viewProjMatrix[3][0];

        normalize(planes[0]);
        //std::cout << "Right : " << planes[0].x << ", " << planes[0].y << ", " << planes[0].z << ", " << planes[0].w  << '\n';

       



        planes[1].x = viewProjMatrix[0][3] - viewProjMatrix[0][0];
        planes[1].y = viewProjMatrix[1][3] - viewProjMatrix[1][0];
        planes[1].z = viewProjMatrix[2][3] - viewProjMatrix[2][0];
        planes[1].w = viewProjMatrix[3][3] - viewProjMatrix[3][0];
        normalize(planes[1]);

        
        

        //std::cout << "Left : " << planes[1].x << ", " << planes[1].y << ", " << planes[1].z<< ", " << planes[1].w  << '\n';
        
        planes[2].x = viewProjMatrix[0][3] - viewProjMatrix[0][1];
        planes[2].y = viewProjMatrix[1][3] - viewProjMatrix[1][1];
        planes[2].z = viewProjMatrix[2][3] - viewProjMatrix[2][1];
        planes[2].w = viewProjMatrix[3][3] - viewProjMatrix[3][1];
        normalize(planes[2]);

        

       // std::cout << "Bottom : " << planes[2].x << ", " << planes[2].y << ", " << planes[2].z<< ", " << planes[2].w <<  '\n';
        
        planes[3].x = viewProjMatrix[0][3] + viewProjMatrix[0][1];
        planes[3].y = viewProjMatrix[1][3] + viewProjMatrix[1][1];
        planes[3].z = viewProjMatrix[2][3] + viewProjMatrix[2][1];
        planes[3].w = viewProjMatrix[3][3] + viewProjMatrix[3][1];
        normalize(planes[3]);

    
        
        

        //std::cout << "Top : " << planes[3].x << ", " << planes[3].y << ", " << planes[3].z<< ", " << planes[3].w <<  '\n';
        
        planes[4].x = viewProjMatrix[0][3] + viewProjMatrix[0][2];
        planes[4].y = viewProjMatrix[1][3] + viewProjMatrix[1][2];
        planes[4].z = viewProjMatrix[2][3] + viewProjMatrix[2][2];
        planes[4].w = viewProjMatrix[3][3] + viewProjMatrix[3][2];
        normalize(planes[4]);
        
        

        //std::cout << "Near : " << planes[4].x << ", " << planes[4].y << ", " << planes[4].z << "," << planes[4].w << '\n';
        
        planes[5].x = viewProjMatrix[0][3] - viewProjMatrix[0][2];
        planes[5].y = viewProjMatrix[1][3] - viewProjMatrix[1][2];
        planes[5].z = viewProjMatrix[2][3] - viewProjMatrix[2][2];
        planes[5].w = viewProjMatrix[3][3] - viewProjMatrix[3][2];
        normalize(planes[5]);

        //std::cout << "Far : " << planes[5].x << ", " << planes[5].y << ", " << planes[5].z << ", " << planes[5].w << '\n';
        
        
    }

        bool isChunkInFrustum(const glm::vec3 & origin, float chunkSize) const {
            glm::vec3 min = origin - glm::vec3(chunkSize /2.f  );
            glm::vec3 max = origin + glm::vec3(chunkSize /1.1f) ;
        
            bool ok = false;
            for(int i = 0; i < 6 ; i++) {
                int out = 0;
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, min.z, 1.f))  < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, min.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, min.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(min.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                out += ((glm::dot(planes[i], glm::vec4(max.x, max.y, max.z, 1.f)) < 0.f) ? 1 : 0);
                if(out == 8) {
                    return false;
                }
            }
            /*
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x > max.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].x < min.x)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y > max.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].y < min.y)? 1 : 0); if(out == 8) return false;
            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z > max.z)? 1 : 0); if(out == 8) return false;

            out = 0; for(int i = 0 ; i < 8 ; i++) out += ((planes[i].z < min.z)? 1 : 0); if(out == 8) return false;
            */
            
            return true;
        }
};

class QuadTreeNode {
    struct Quad {
        glm::vec2 position;
        glm::vec2 size;

        Quad(glm::vec2 position, glm::vec2 size) : position(position), size(size) {}

        bool isInside(const glm::vec2 & point) const {
            //return point.x >= position.x && point.x <= position.x + size.x && point.y >= position.y && point.y <= position.y + size.y;
            return !(position.x + size.x / 2 < point.x || position.x - size.x / 2 > point.x || position.y + size.y / 2 < point.y || position.y - size.y / 2 > point.y);
        }
    };

    static constexpr int MAX_QUADS = 4;
    static constexpr int MAX_LEVELS = 5;

    glm::vec2 position;
    glm::vec2 size;

    std::vector<std::unique_ptr<QuadTreeNode>> children;

    std::vector<Quad> quads;
    int level;

    public:

    QuadTreeNode(glm::vec2 position, glm::vec2 size, int level) : position(position), size(size), level(level) {}

    void subdivide() {
        if(!children.empty()) return ;

        glm::vec2 halfSize = size / 2.f;
        glm::vec2 offsets[] = {
            {-halfSize.x / 2, - halfSize.y / 2},
            {halfSize.x / 2, - halfSize.y / 2},
            {-halfSize.x / 2, halfSize.y / 2},
            {halfSize.x / 2, halfSize.y / 2}
        };

        for(const auto & offset : offsets) {
            children.push_back(std::make_unique<QuadTreeNode>(position + offset, halfSize, level + 1));
        }
    }
    
    bool contains(const Quad& quad) const {
        return !(position.x + size.x / 2 < quad.position.x - quad.size.x / 2 || position.x - size.x / 2 > quad.position.x + quad.size.x / 2 || position.y + size.y / 2 < quad.position.y - quad.size.y / 2 || position.y - size.y / 2 > quad.position.y + quad.size.y / 2);
    }

    void insert(const Quad& quad) {
        if(!contains(quad)) return ;

        if(children.empty() || level == MAX_LEVELS) {
            quads.push_back(quad);
            return ;
        }

        if(children.empty()) subdivide();

        for(auto & child : children) {
            child -> insert(quad);
        }

        
    }

    bool isOccluded(const Quad & quad) const {
        for (const auto &q : quads) {
            if(q.isInside(quad.position)) {
                return true;
            }
        }

        for(const auto & child : children) {
            if(child -> isOccluded(quad)) {
                return true;
            }
        }
        return false;
    }
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
        SubChunk(glm::vec3 origin);
        ~SubChunk();
        void Render(glm::mat4 view, glm::mat4 projection);
        std::vector<std::shared_ptr<Rigidbody>> Update(float deltaTime);
        void LoadChunk();
        void GenerateChunk();

        glm::vec3 GetOrigin() {
            return origin;
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

        std::vector<std::shared_ptr<Rigidbody>> Update(float deltaTime, glm::vec3 playerPosition, float diameter, glm::mat4 ProjView);

        void LoadChunk();

        glm::vec3 GetOrigin() {
            return origin;
        }

};