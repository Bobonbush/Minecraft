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

    Item(int number);
    ~Item();

    virtual void Render() = 0;
    virtual void update() = 0;
    virtual Stats getStats() = 0;

    void addNumber(int number) {
        stats.number += number;
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

};

class BlockItem : public Item {
    private:
        CubeRenderer * cubeRenderer;
        BLOCKID id;
        BlockData data;
    public:
        BlockItem(BLOCKID id, int number, const std::string& name);
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