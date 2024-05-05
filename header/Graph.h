#ifndef DA_SECONDPROJECT_GRAPH_H
#define DA_SECONDPROJECT_GRAPH_H

class Vertex;

#include "Vertex.h"
#include <vector>

class Graph{
private:
    std::vector<std::shared_ptr<Vertex>> vertexSet; /// Vector tha holds all vertexes that belong to the graph
public:
    /**
     * @brief Returns the vertex set of the graph.
     *
     * @return Vertex set
     */
    const std::vector<std::shared_ptr<Vertex>>& getVertexSet() const;
    /**
     * @brief Adds a vertex to the graph
     * @param Vertex Pointer to the vertex being added.
     */
    void addVertex(const std::shared_ptr<Vertex>& vertex);
    /**
     * @brief Used to find a vertex on the graph
     *
     * @param code Identifies the code of the vertex being looked for
     * @return Returns a pointer to the vertex being looked for or nullptr otherwise
     */
    std::shared_ptr<Vertex> findVertex(uint32_t code) const;
};

#endif
