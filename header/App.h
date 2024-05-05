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
public:
    /**
     * @brief Allows the application to be initialized the right way
     */
    void init();
    bool functionalities();
};

#endif
