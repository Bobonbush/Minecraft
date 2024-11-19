#ifndef MESH_H
#define MESH_H
#include <GLAD/glad.h>
#include <vector>
class Mesh {
    public:

    std::vector<GLfloat> vertexPosition;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint> indices;
};

#endif