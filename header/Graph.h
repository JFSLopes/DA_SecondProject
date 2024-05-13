#ifndef DA_SECONDPROJECT_GRAPH_H
#define DA_SECONDPROJECT_GRAPH_H

class Vertex;

#include "Vertex.h"
#include <vector>
#include <map>

/**
 * @class Graph
 * @brief Stores information in a graph structure
 */
class Graph{
private:
    std::vector<std::shared_ptr<Vertex>> vertexSet; ///< Vector tha holds all vertexes that belong to the graph

    /**
     * @brief Used the Prim algorithm to find a MST
     *
     * @param s Source Vertex
     * @return Return a vector with the Vertex used in the mst
     */
    std::vector<std::shared_ptr<Vertex>> prim(const std::shared_ptr<Vertex>& s) const;
    /**
     * @brief Finds the preorder on the graph
     *
     * @param s Source Vertex
     * @param pre_order Vector that will contain the vertex in preorder
     */
    void pre_order(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Vertex>>& pre_order) const;
    /**
     * @brief Sets the 'in' and 'out' parameters of all vertexes
     */
    void set_in_out_degree();
    /**
     * @brief Finds the minimal matching between all vertex with odd degree (Used in Christofides)
     */
    void findMinimumWeightPerfectMatching();
    /**
     * @brief Finds an Eulerian circuit (Used in Christofides)
     *
     * @param visitedVertices Vector that will store all vertex vesited during the algorithm
     */
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
     * @param vertex Pointer to the vertex being added.
     */
    void addVertex(const std::shared_ptr<Vertex>& vertex);
    /**
     * @brief Used to find a vertex on the graph
     *
     * @param code Identifies the code of the vertex being looked for
     * @return Returns a pointer to the vertex being looked for or nullptr otherwise
     */
    std::shared_ptr<Vertex> findVertex(uint32_t code) const;
    /**
     * @brief Implements the triangular approximation algorithm for TSP
     *
     * @param s Source Vertex
     * @param path Vector that will store the hamiltonian path
     * @return True if a hamiltonian was found, false otherwise
     */
    bool triangular_approximation(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& path) const;
    /**
     * @brief Makes the graph fully connected if possible
     *
     * @param num_edges Number os edges the graph has
     */
    void fully_connected(uint64_t& num_edges);
    /**
     * @brief Implements the Christofides algorithm for the TSP
     *
     * @param s Source Vertex
     * @param hamiltonian Vector that will store the hamiltonian path
     * @return True if a hamiltonian was found, false otherwise
     */
    bool Christofides(const std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& hamiltonian);
    /**
     * @brief Implements the NN algorithm for the TSP
     *
     * @param s Source Vertex
     * @param hamiltonian Vector that will store the hamiltonian path
     * @return True if a hamiltonian was found, false otherwise
     */
    bool nearest_neighbour(const std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& hamiltonian);
};

#endif
