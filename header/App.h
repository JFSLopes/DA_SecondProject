#ifndef DA_SECONDPROJECT_APP_H
#define DA_SECONDPROJECT_APP_H

class Graph;

#include "Graph.h"

/**
 * @class App
 * @brief Controls the flow of the application
 */
class App {
private:
    std::unique_ptr<Graph> g; ///< Pointer to the graph structure that represents the network
    uint32_t num_nodes; ///< Number of nodes in g
    uint64_t num_edges = 0; ///< Number of edges in g
    std::string nodes;  ///< Nodes file name
    std::string edges; ///< Edges file name
    std::string path; ///< Path to the directory containing the files
    bool header; ///< True if the edges file has a header
    bool edges_only; ///< True if there is only a edges file
    uint32_t num_nodes_file; ///< Number of nodes to be loaded
    bool made_fully_connected = false; ///< True if the graph has made fully connected, False otherwise
    /**
     * @brief Finds the best hamiltonian path using a simple using backtracking algorithm
     * @param s Current vertex being processed
     * @param d Destination vertex (It must be the vertex used in the start)
     * @param curr_path Current path being tested
     * @param best_path Stores the best hamiltonian path if one is found
     * @param size_hamiltonian Number of edges the path must have to be a hamiltonian
     * @param path_sum Current sum of all distances in curr_path (allows to no recompute the distances)
     * @param best_sum Total distance of the best_path
     */
    void find_best_hamiltonian(
            std::shared_ptr<Vertex>& s,
            std::shared_ptr<Vertex>& d,
            std::vector<std::shared_ptr<Edge>>& curr_path,
            std::vector<std::shared_ptr<Edge>>& best_path,
            uint32_t size_hamiltonian,
            double& path_sum,
            double& best_sum) const;

    /**
     * @brief Checks if I graph is fully connected, if it is not, then it will make it become one
     *
     * @return True if is possible to make the graph fully connected, false otherwise
     */
    bool make_fully_connected();
public:
    /**
     * @brief Allows the application to be initialized the right way
     */
    void init();
    /**
     * @brief Controls the flow the app flow
     *
     * @return True if the user wants to reload another set of files, False if he wants to close the app
     */
    bool functionalities();
    /**
     * @brief Generate all possible paths that are hamiltonian and choose the shortest
     */
    void backtracking() const;
    /**
     * @brief Algorithm to find hamiltonian paths
     *
     * This algorithm has the following steps:
     *      1. Find a mst (We are using Prim with a mutable priority queue)
     *      2. After finding the mst, find a preorder for the vertex (only using the edges used in the mst)
     *      3. If there is edges between the pre-ordered vertex, then that is the hamiltonian
     *
     * Step 2 is necessary, because allows the final path to have the most number of edges used in the mst, which allow
     * the approximation to be at most 2 times worst than the optimal solution
     */
    void triangular_approximation();
    /**
     * @brief Christofides algorithm
     *
     * The algorithm has the following steps
     *      1. Get a MST. Let's call it T
     *      2. Select the vertices from the mst with odd degree. Let's call it O
     *      3. Find a minimum weight perfect matching on the vertices on O. Let's call it M
     *      4. Combine M and T
     */
    void other_heuristic();
    /**
     * @brief Nearest Neighbour (NN) algorithm
     *
     * This algorithm has the following steps:
     *      1. Choose a initial vertex (In the app case, is the vertex with label 0)
     *      2. Find the closest vertex and that vertex becomes the current vertex.
     *      3. Keeps repeating step 2 until all vertex are visited or there is no hamiltonian path
     */
    void nearest_neighbour();
    /**
     * @brief Algorithm to the real world graph
     *
     * The algorithm used is the NN because is really fast and the result are is a reasonable distance from the optimal
     * solution.
     */
    void TSP_Real_World() const;
};

#endif
