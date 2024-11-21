#include "RenderMaster.h"


RenderMaster::RenderMaster() {
    quadRenderer = std::make_unique<QuadRenderer>();
    cubeRenderer = std::make_unique<CubeRenderer>();
    chunkRenderer = std::make_unique<ChunkRenderer>();
}

void RenderMaster::drawChunk(const ChunkMesh & mesh) {
    chunkRenderer -> add(mesh);
}
void RenderMaster::drawQuads(const glm::vec3 & pos) {
    quadRenderer -> add(pos);
}

void RenderMaster::drawCubes(const glm::vec3 & pos) {
    cubeRenderer -> add(pos);
}

void RenderMaster::finishRender(const glm::mat4 & view, const glm::mat4 & projection) {
    //quadRenderer -> renderQuads(view , projection);
    //cubeRenderer -> renderCubes(view, projection);   
    chunkRenderer -> render(view, projection);
}