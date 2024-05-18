#include "../header/Vertex.h"
#include <algorithm>
#include <cfloat>

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

uint32_t Vertex::getDegree() const {
    return in + out;
}


void Vertex::order_edges() {
    auto comp = [] (const std::shared_ptr<Edge>& e1, const std::shared_ptr<Edge>& e2){
        if (e1->getDest()->getDegree() < e2->getDest()->getDegree()) return true;
        else if (e1->getDest()->getDegree() == e2->getDest()->getDegree() and e1->getWeight() < e2->getWeight()) return true;
        return false;
    };
    std::sort(adj.begin(), adj.end(), comp);
}

bool operator<(const Vertex& a, const Vertex& b){
    return a.getDist() < b.getDist();
}