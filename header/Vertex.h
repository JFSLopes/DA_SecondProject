#ifndef DA_SECONDPROJECT_VERTEX_H
#define DA_SECONDPROJECT_VERTEX_H

class Edge;

#include "Edge.h"
#include "Coordinates.h"
#include <vector>
#include <memory>

class Vertex {
private:
    uint32_t code; /// Id of the vertex
    Coordinates coordinates;
    std::vector<std::shared_ptr<Edge>> adj; /// Represents the edges that have the vertex as origin
    bool visited; /// Flag to check if the vertex has already been visited
    std::shared_ptr<Edge> path; /// Pointer to an edge included in an augmenting path
public:
    Vertex(uint32_t info, double lat, double lon);

    uint32_t getCode() const;
    const std::vector<std::shared_ptr<Edge>>& getAdj() const;
    const Coordinates& getCoordinates() const;
    const std::shared_ptr<Edge>& getPath() const;
    bool isVisited() const;

    void addEdge(const std::shared_ptr<Vertex>& d, double distance);
};

#endif
