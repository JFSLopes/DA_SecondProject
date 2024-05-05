#include "../header/Graph.h"

const std::vector<std::shared_ptr<Vertex>>& Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::addVertex(const std::shared_ptr<Vertex>& vertex) {
    vertexSet.push_back(vertex);
}

std::shared_ptr<Vertex> Graph::findVertex(uint32_t code) const {
    for (const std::shared_ptr<Vertex>& ptr : vertexSet){
        if (ptr->getCode() == code) return ptr;
    }
    return nullptr;
}