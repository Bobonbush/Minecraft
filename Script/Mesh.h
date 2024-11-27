#ifndef MESH_H
#define MESH_H
#include <GLAD/glad.h>
#include <vector>
class Mesh {
    public:

    std::vector<GLfloat> vertexPosition;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint> indices;
    std::vector<GLfloat> normals;

    Mesh(std::vector<GLfloat> vertexPosition, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices) : vertexPosition(vertexPosition), textureCoords(textureCoords), indices(indices) {}
    Mesh() = default;
};

#endif