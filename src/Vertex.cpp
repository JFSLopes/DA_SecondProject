#include "../header/Vertex.h"

Vertex::Vertex(uint32_t code, double lat, double lon) : code(code), coordinates(Coordinates(lat, lon)), in(0), out(0) {}

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

void Vertex::setPath(std::shared_ptr<Edge> e) {
    path = e;
}

void Vertex::setIn(uint32_t value) {
    in = value;
}

void Vertex::setOut(uint32_t value) {
    out = value;
}

uint32_t Vertex::getIn() const {
    return in;
}

uint32_t Vertex::getOut() const {
    return out;
}

void Vertex::addEdge(const std::shared_ptr<Vertex> &s, const std::shared_ptr<Vertex> &d, double distance) {
    std::shared_ptr<Edge> edge = std::make_shared<Edge>(s, d, distance);
    adj.push_back(edge);
}

std::shared_ptr<Edge> Vertex::findEdge(const std::shared_ptr<Vertex> &d) const {
    for (const std::shared_ptr<Edge>& e : adj){
        if (e->getDest()->getCode() == d->getCode()){
            return e;
        }
    }
    return nullptr;
}

bool operator<(const Vertex& a, const Vertex& b){
    return a.getDist() < b.getDist();
}