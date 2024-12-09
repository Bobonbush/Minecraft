#ifndef ITEM_H
#define ITEM_H
#include "Texture.h"
#include "Block/BlockDataBase.h"
#include "Model.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/SpriteRenderer.h"
#include "Config.h"
class Item {
    

    public:
    
    const int maxStack = 64;
    struct Stats {
        int number;
        BLOCKID id;
        

        const bool operator == (const Stats & other) const {
            return number == other.number && id == other.id;
        }
    };

    protected :
    std::string type = "Item";

    Stats stats;
    glm::vec3 position;
    public :

    Item();
    ~Item();

    virtual void Render() = 0;
    virtual void update() = 0;
    virtual Stats getStats() = 0;

    int addNumber(int number) {
        stats.number += number;
        int lefty = SPA::max(0, stats.number - maxStack);
        SPA::clamp(stats.number, 0, maxStack);
        return lefty;
    }

    void use() {
        stats.number--;
    }

    void setPosition(const glm::vec3 & pos) {
        position = pos;
    }

    const bool operator == (const Item & other) const {
        return stats == other.stats;
    }

    const std::string & getType() const {
        return type;
    }

    const BLOCKID getID() const {
        return stats.id;
    }

    const int getNumber() const {
        return stats.number;
    }

    bool isFull() {
        return stats.number == maxStack;
    }

};

class BlockItem : public Item {
    private:
        CubeRenderer * cubeRenderer;
        BLOCKID id;
        BlockData data;
    public:
        BlockItem(BLOCKID id, const std::string& name);
        ~BlockItem();
        void Render() override;
        void update() override;
        Stats getStats() override;

};

class SpriteItem : public Item {
    private:
        SpriteRenderer * spriteRenderer;
        unsigned int texture;
    public:
        SpriteItem(const std::string & path, int number);
        ~SpriteItem();
        void Render() override;
        void update() override;
        Stats getStats();

        
};

#endif // ITEM_H