#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        // constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        // render the mesh
        void Draw(Shader &  shader);
    private:
        // render data
        unsigned int VAO, VBO, EBO;
        // initializes all the buffer objects/arrays
        void setupMesh();
};

class Model {
    public:
        // model data
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;
        // constructor, expects a filepath to a 3D model.
        Model(std::string const &path, bool gamma = false);
        // draws the model, and thus all its meshes
        void Draw(Shader & shader);

        
    private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        void loadModel(std::string const &path);
        
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
        {
            std::string filename = std::string(path);
            filename = directory + '/' + filename;
        
            unsigned int textureID;
            glGenTextures(1, &textureID);
        
            int width, height, nrComponents;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;
        
                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
        
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }
        
            return textureID;
    }
};