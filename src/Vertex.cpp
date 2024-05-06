#include "../header/Vertex.h"

Vertex::Vertex(uint32_t code, double lat, double lon) : code(code), coordinates(Coordinates(lat, lon)) {}

uint32_t Vertex::getCode() const {
    return code;
}

double Vertex::getDist() const {
    return dist;
}

const std::vector<std::shared_ptr<Edge>>& Vertex::getAdj() const {
    return adj;
}

const Coordinates &Vertex::getCoordinates() const {
    return coordinates;
}

const std::shared_ptr<Edge>& Vertex::getPath() const {
    return path;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool cond) {
    visited = cond;
}

void Vertex::setDist(double distance) {
    dist = distance;
}

void Vertex::addEdge(const std::shared_ptr<Vertex> &s, const std::shared_ptr<Vertex> &d, double distance) {
    std::shared_ptr<Edge> edge = std::make_shared<Edge>(s, d, distance);
    adj.push_back(edge);
}
