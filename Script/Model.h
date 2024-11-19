#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include "Renderer/RenderInfo.h"
#include <iostream>
class Model {
    private:
    RenderInfo renderInfo;
    int m_vboCount = 0;
    std::vector<GLuint> buffers;

    public:

    Model() = default;
    Model(const Mesh & mesh);
    ~Model();

    Model(Model & another);

    Model &operator = (Model & another);

    void addData(const Mesh & mesh);

    void deleteData();

    void genVAO();

    void addVBO(int dim, const std::vector<GLfloat> &data);
    void addEBO(const std::vector<GLuint> &data);

    void bindVao() const;

    int getVertexCount() const;
    int getIndicesCount() const;

    const RenderInfo & getRenderInfo() const;

     
};

#endif