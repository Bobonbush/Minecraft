#include "RenderMaster.h"


RenderMaster::RenderMaster() {
    quadRenderer = std::make_unique<QuadRenderer>();
}
void RenderMaster::drawQuads(const glm::vec3 & pos) {
    quadRenderer -> add(pos);

}

void RenderMaster::finishRender(const glm::mat4 & view, const glm::mat4 & projection) {
    quadRenderer -> renderQuads(view , projection);
    
}