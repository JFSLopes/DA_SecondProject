#include "../header/Edge.h"

Edge::Edge(std::shared_ptr<Vertex> dest, double weight)
        : dest(std::move(dest)), weight(weight) {}


double Edge::getWeight() const {
    return weight;
}

std::shared_ptr<Vertex> Edge::getDest() const {
    return dest;
}
