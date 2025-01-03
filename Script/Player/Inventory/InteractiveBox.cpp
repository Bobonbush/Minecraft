#include "InteractiveBox.h"


InventoryBox::InventoryBox(glm::vec2 position, glm::vec2 size, int number, const std::string& off, const State & state) : m_position(position), m_size(size), number(number) {
    TextureManager * textureManager = TextureManager::getInstance();
    m_texture[0] = textureManager -> getTexture(off.c_str());
    m_texture[1] = textureManager -> getTexture("Assets/Inventory/on.png");
    m_spriteRenderer = SpriteRenderer::getInstance();

    textLoader = std::make_unique<TextHandler>();
    textLoader -> LoadFont("Assets/Font/Mantinia.otf", 24);
    

    if(state != State::None) {
        //item = std::make_shared<Item>(state);
        //empty = false;
        hasFake = true;
        if(state == State::HEAD) {
            fakeTexture = textureManager -> getTexture("Assets/Inventory/head.png");
            
        }
        else if(state == State::BODY) {
            fakeTexture = textureManager -> getTexture("Assets/Inventory/body.png");
        }
        else if(state == State::LEG) {
            fakeTexture = textureManager -> getTexture("Assets/Inventory/leg.png");
        }
        else if(state == State::Boot) {
            fakeTexture = textureManager -> getTexture("Assets/Inventory/boot.png");
        }
    }


}

InventoryBox::~InventoryBox() {
    
}

void InventoryBox::update() {
    if(item != nullptr) {
        item -> update();
        item -> setPosition(glm::vec3(m_position, 0.f));
    }
}

void InventoryBox::Render() {
    Config * config = Config::GetInstance();
    glDisable(GL_DEPTH_TEST);

    if(!empty) {
        ItemDataBase * itemDataBase = ItemDataBase::GetInstance();
        if(m_chosen) {

        
            std::string name = itemDataBase -> getItemName(item -> getID());
            Config * config = Config::GetInstance();
            SPA::LowerCase(name);
            
            
            ShaderManager::GetInstance() -> getShader("text") -> use();
            
            ShaderManager::GetInstance() -> getShader("text") -> setFloat("alpha", 1.0f);
            textLoader -> RenderMiddleText(name, m_position.x + m_size.x / 3.5f, m_position.y + m_size.y / 1.8f, 1.5f,  glm::vec3(0.8f , 0.2f, 0.8f), 0 , glm::vec2(config -> GetWidth(), config -> GetHeight()));
            
        }
    }
    
    ShaderManager * shaderManager = ShaderManager::GetInstance();
    m_spriteRenderer -> setShader(shaderManager -> getShader("Screen"));
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    m_spriteRenderer -> DrawSprite(m_texture[m_chosen], m_position, m_size, 0.f, glm::vec3(1.f), view , projection);
    
    
    if(!empty) {
        
        item -> Render();
    }
    m_chosen = false;

    if(hasFake && empty) {
        m_spriteRenderer -> setShader(ShaderManager::GetInstance() -> getShader("Screen"));
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        m_spriteRenderer -> DrawSprite(fakeTexture, m_position , m_size /1.2f, 0.f, glm::vec3(1.f), view , projection);
    }

    
    

    glEnable(GL_DEPTH_TEST);
    
} 

void InventoryBox::isChosen() {
    m_chosen = true;
}


void InventoryBox::setItem(std::shared_ptr<Item> _item) {
    item = _item;
    empty = false;
}

void InventoryBox::unsetItem() {
    item = nullptr;
    empty = true;
}

bool InventoryBox::isEmpty() {
    return empty;
}

bool InventoryBox::Choose() {
    return m_chosen;
}


bool InventoryBox::isMouseOnBox(const float& xpos , const float& ypos) {
    return xpos >= m_position.x - m_size.x/2.f && xpos <= m_position.x + m_size.x/2.f && ypos >= m_position.y - m_size.y/2.f && ypos <= m_position.y + m_size.y/2.f;
}


std::shared_ptr<Item> InventoryBox::getItem() {
    return item;
}

const glm::vec2 InventoryBox::getPosition() const {
    return m_position;
}




