#include "RenderMaster.h"


RenderMaster::RenderMaster() {
    chunkRenderer = std::make_unique<ChunkRenderer>();
    skybox = std::make_unique<SkyBox>();
}

void RenderMaster::drawChunk(const ChunkMesh & mesh, const ChunkMesh & waterMesh) {
    chunkRenderer -> add(mesh, waterMesh);
}
void RenderMaster::drawQuads(const glm::vec3 & pos) {
}

void RenderMaster::drawCubes(const glm::vec3 & pos) {

}

void RenderMaster::finishRender(const glm::mat4 & view, const glm::mat4 & projection) {
    //quadRenderer -> renderQuads(view , projection);
    //cubeRenderer -> renderCubes(view, projection);   
    
    chunkRenderer -> render(view, projection);
    skybox -> render(view, projection);
}