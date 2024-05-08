#ifndef DA_SECONDPROJECT_VERTEX_H
#define DA_SECONDPROJECT_VERTEX_H

class Edge;

#include "Edge.h"
#include "Coordinates.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <memory>

class Vertex {
private:
    uint32_t code; /// Id of the vertex
    Coordinates coordinates;
    std::vector<std::shared_ptr<Edge>> adj; /// Represents the edges that have the vertex as origin
    bool visited; /// Flag to check if the vertex has already been visited
    std::shared_ptr<Edge> path; /// Pointer to an edge included in an augmenting path
    double dist;
    uint32_t in;
    uint32_t out;
public:
    Vertex(uint32_t info, double lat, double lon);

    uint32_t getCode() const;
    double getDist() const;
    uint32_t getIn() const;
    uint32_t getOut() const;
    const std::vector<std::shared_ptr<Edge>>& getAdj() const;
    const Coordinates& getCoordinates() const;
    const std::shared_ptr<Edge>& getPath() const;
    bool isVisited() const;

    void setVisited(bool cond);
    void setDist(double distance);
    void setPath(std::shared_ptr<Edge> e);
    void setIn(uint32_t value);
    void setOut(uint32_t value);

    void addEdge(const std::shared_ptr<Vertex> &s, const std::shared_ptr<Vertex>& d, double distance);
    std::shared_ptr<Edge> findEdge(const std::shared_ptr<Vertex>& d) const;


    friend class MutablePriorityQueue<Vertex>;
protected:
    int queueIndex = 0;
};

bool operator<(const Vertex& a, const Vertex& b);

#endif
