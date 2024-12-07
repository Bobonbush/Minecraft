#include "Texture.h"
#include "Texture&Shader/TextureAtlas.h"

class Weapon {
    private :
        std::unique_ptr<TextureAtlas>  atlas;
        std::shared_ptr<Shader> shader;
    public :
        Weapon();
        ~Weapon();
        void Render();
        void update();
        void setShader(std::shared_ptr<Shader> _shader) {
            shader = _shader;
        }
        void setAtlas(const std::string & path) {
            atlas = std::make_unique<TextureAtlas>(path);
        }
        void setAtlas(std::unique_ptr<TextureAtlas> _atlas) {
            atlas = std::move(_atlas);
        }
        std::unique_ptr<TextureAtlas> & getAtlas() {
            return atlas;
        }
        std::shared_ptr<Shader> getShader() {
            return shader;
        }
};