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
    /// Pointer to the graph structure that represents the network
    std::unique_ptr<Graph> g;

    void find_best_hamiltonian(
            std::shared_ptr<Vertex>& s,
            std::shared_ptr<Vertex>& d,
            std::vector<std::shared_ptr<Edge>>& curr_path,
            std::vector<std::shared_ptr<Edge>>& best_path,
            uint32_t size_hamiltonian,
            double& path_sum,
            double& best_sum) const;
public:
    /**
     * @brief Allows the application to be initialized the right way
     */
    void init();
    bool functionalities();
    /**
     * @brief Generate all possible paths that are hamiltonian and choose the shortest
     */
    void backtracking() const;
    void triangular_approximation() const;
    void other_heuristic() const;
    void TSP_Real_World() const;
};

#endif
