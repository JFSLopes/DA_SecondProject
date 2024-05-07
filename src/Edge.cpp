#include "../header/Edge.h"

Edge::Edge(std::shared_ptr<Vertex> orig, std::shared_ptr<Vertex> dest, double weight)
        : orig(orig), dest(std::move(dest)), weight(weight) {}


double Edge::getWeight() const {
    return weight;
}

std::shared_ptr<Vertex> Edge::getDest() const {
    return dest;
}

std::shared_ptr<Vertex> Edge::getOrig() const {
    return orig;
}

bool Edge::isSelected() const {
    return selected;
}

void Edge::setSelected(bool cond) {
    selected = cond;
}

void Edge::setWeight(double w) {
    weight = w;
}