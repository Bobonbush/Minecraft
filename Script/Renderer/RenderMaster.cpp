#include "RenderMaster.h"


RenderMaster::RenderMaster() {
    quadRenderer = std::make_unique<QuadRenderer>();
    chunkRenderer = std::make_unique<ChunkRenderer>();
    skybox = std::make_unique<SkyBox>();
}

void RenderMaster::drawChunk(const ChunkMesh & mesh) {
    chunkRenderer -> add(mesh);
}
void RenderMaster::drawQuads(const glm::vec3 & pos) {
    quadRenderer -> add(pos);
}

void RenderMaster::drawCubes(const glm::vec3 & pos) {

}

void RenderMaster::finishRender(const glm::mat4 & view, const glm::mat4 & projection) {
    //quadRenderer -> renderQuads(view , projection);
    //cubeRenderer -> renderCubes(view, projection);   
    
    chunkRenderer -> render(view, projection);
    skybox -> render(view, projection);
}