#include "ChunkMesh.h"

ChunkMesh::ChunkMesh() {
}

void ChunkMesh::addFace(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> &texcoords, const glm::vec3 &position, const glm::vec3 &blockPosition) {
    std::vector<GLfloat> &m_vertices = mesh.vertexPosition;
    std::vector<GLfloat> &m_coords = mesh.textureCoords;
    std::vector<GLuint> &m_indices = mesh.indices;

    m_coords.insert(m_coords.end(), texcoords.begin(), texcoords.end());

    for(int i = 0 , index =0 ; i < 4 ; i++) {
        m_vertices.push_back(vertices[index++] + position.x * Chunk::CHUNK_SIZE + blockPosition.x);
        m_vertices.push_back(vertices[index++] + position.y * Chunk::CHUNK_SIZE + blockPosition.y);
        m_vertices.push_back(vertices[index++] + position.z * Chunk::CHUNK_SIZE + blockPosition.z);
    }

    m_indices.insert(m_indices.end(), {
        indexIndex, indexIndex + 1, indexIndex + 3, 
        indexIndex + 1, indexIndex + 2, indexIndex + 3
    });

    indexIndex += 4;
}

void ChunkMesh::bufferMesh() {
    std::cout << "Buffering Mesh" << std::endl;
    std::cout << mesh.vertexPosition.size() << std::endl;
    std::cout << mesh.textureCoords.size() << std::endl;
    std::cout << mesh.indices.size() << std::endl;

    Chunkmodel.addData(mesh);

    mesh.vertexPosition.clear();
    mesh.textureCoords.clear();
    mesh.indices.clear();
    indexIndex = 0;

    mesh.vertexPosition.shrink_to_fit();
    mesh.textureCoords.shrink_to_fit();
    mesh.indices.shrink_to_fit();
}

const Model & ChunkMesh::getModel() const {
    return Chunkmodel;
}