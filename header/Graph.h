#ifndef DA_SECONDPROJECT_GRAPH_H
#define DA_SECONDPROJECT_GRAPH_H

class Vertex;

#include "Vertex.h"
#include <vector>
#include <map>

class Graph{
private:
    std::vector<std::shared_ptr<Vertex>> vertexSet; /// Vector tha holds all vertexes that belong to the graph

    std::vector<std::shared_ptr<Vertex>> prim(const std::shared_ptr<Vertex>& s) const;
    void pre_order(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Vertex>>& pre_order) const;
    void set_in_out_degree();
    void findMinimumWeightPerfectMatching();
    void formEulerianCircuit(std::vector<std::shared_ptr<Vertex>>& visitedVertices);
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
    bool triangular_approximation(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& path) const;
    void fully_connected(uint64_t& num_edges);
    bool Christofides(const std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& hamiltonian);
    bool nearest_neighbour(const std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& hamiltonian);
};

#endif
