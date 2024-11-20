#include "Model.h"


Model::Model(const Mesh & mesh) {
    addData(mesh);
}

Model::~Model() {
    deleteData();
}

Model::Model(Model & another) {
    renderInfo = another.renderInfo;
    m_vboCount = another.m_vboCount;
    buffers = another.buffers;

    another.m_vboCount = 0;
    another.renderInfo.reset();
}

Model & Model::operator = (Model & another) {
    if(this == &another) {
        return *this;
    }

    renderInfo = another.renderInfo;
    m_vboCount = another.m_vboCount;
    buffers = another.buffers;

    another.m_vboCount = 0;
    another.renderInfo.reset();

    return *this;
}

void Model::genVAO() {
    if(renderInfo.vao != 0) {
        deleteData();
    }
    glGenVertexArrays(1, &renderInfo.vao);
    glBindVertexArray(renderInfo.vao);
}

void Model::bindVao() const {
    glBindVertexArray(renderInfo.vao);
}

void Model::addData(const Mesh & mesh) {
    genVAO();
    addVBO(3, mesh.vertexPosition);


    addVBO(2, mesh.textureCoords);

    addEBO(mesh.indices);

    renderInfo.indicesCount = static_cast<GLuint>(mesh.indices.size());

    glBindVertexArray(0);
}

void Model::addVBO(int dim, const std::vector<GLfloat> &data) {
    GLuint vbo;

    glGenBuffers(1, &vbo);
    
    //glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(static_cast<GLuint>(m_vboCount), dim, GL_FLOAT, GL_FALSE, dim * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    buffers.push_back(vbo);
    m_vboCount++;
}

void Model::addEBO(const std::vector<GLuint> & indices) {
    renderInfo.indicesCount = static_cast<GLuint>(indices.size());

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    buffers.push_back(ebo);
}

void Model::deleteData() {
    if(renderInfo.vao != 0) {
        glDeleteVertexArrays(1, &renderInfo.vao);    
    }
    if(buffers.size() > 0) {
        glDeleteBuffers((int)buffers.size(), &buffers[0]);
    }
    renderInfo.reset();
    m_vboCount = 0;
    buffers.clear();
}

int Model::getVertexCount() const {
    return 0;
}

int Model::getIndicesCount() const {
    return renderInfo.indicesCount;
}

const RenderInfo & Model::getRenderInfo() const {
    return renderInfo;
}









