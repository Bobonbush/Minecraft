#ifndef ITEM_H
#define ITEM_H
#include "Texture.h"
#include "Block/BlockDataBase.h"
#include "Model.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/QuadRenderer.h"
#include "Renderer/SpriteRenderer.h"
#include "Config.h"
#include "Player/Inventory.h"
#include "itemDataBase.h"

class Item {
    

    public:
    
    const int maxStack = 64;

    static std::unique_ptr<TextHandler> textLoader;

    struct Stats {
        int number;
        int id;
        
        

        const bool operator == (const Stats & other) const {
            return number == other.number && id == other.id;
        }
    };

    protected :
    std::string type = "Item";

    Stats stats;
    glm::vec3 position;

    bool isHold = false;
    
    public :

    bool isPick = false; 

    Item();
    ~Item();

    virtual void Render() = 0;
    virtual void update() = 0;
    virtual Stats getStats() = 0;
    virtual std::shared_ptr<Item> clone() = 0;

    int addNumber(int number) {
        stats.number += number;
        int lefty = SPA::max(0, stats.number - maxStack);
        SPA::clamp(stats.number, 0, maxStack);
        return lefty;
    }

    int getOne() {
        stats.number--;
        return 1;
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

    const int getID() const {
        return  stats.id;
    }

    const int getNumber() const {
        return stats.number;
    }


    bool isFull() {
        return stats.number == maxStack;
    }

    void PickUp() {
        isPick = true;
    }

    void Drop() {
        isPick = false;
    }

    const glm::vec3 & getPosition() const {
        return position;
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
        std::shared_ptr<Item> clone() override {
            return std::make_shared<BlockItem>(*this);
        }

};

class SpriteItem : public Item {
    private:
        QuadRenderer * quadRenderer;
        ItemDataBase * itemDataBase;
        ItemData data;
    public:
        SpriteItem(ItemID id ,const std::string & name);
        ~SpriteItem();
        void Render() override;
        void update() override;
        Stats getStats() override;

        std::shared_ptr<Item> clone() override {
            return std::make_shared<SpriteItem>(*this);
        }

        
};

#endif // ITEM_H