#ifndef DA_SECONDPROJECT_VERTEX_H
#define DA_SECONDPROJECT_VERTEX_H

class Edge;

#include "Edge.h"
#include "Coordinates.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <memory>

/**
 * @class Vertex
 * @brief Allows to represent the information of any vertex on the graph
 */
class Vertex {
private:
    uint32_t code; ///< Id of the vertex
    Coordinates coordinates; ///< Geographic coordinates of the vertex
    std::vector<std::shared_ptr<Edge>> adj; /// Represents the edges that have the vertex as origin
    bool visited; /// Flag to check if the vertex has already been visited
    std::shared_ptr<Edge> path; /// Pointer to an edge included in an augmenting path
    double dist; ///< Used to store the distance
    uint32_t in; ///< Number of in going edges
    uint32_t out; ///< Number of out going edges
public:
    Vertex(uint32_t info, double lat, double lon);
    /**
     * @return Return the vertex code
     */
    uint32_t getCode() const;
    /**
     * @return Returns the distance stored in dist
     */
    double getDist() const;
    /**
     * @return Returns the number of in going edges
     */
    uint32_t getIn() const;
    /**
     * @return Returns the number of out going edges
     */
    uint32_t getOut() const;
    /**
     * @return Returns the vertex vector that stores its connections
     */
    const std::vector<std::shared_ptr<Edge>>& getAdj() const;
    /**
     * @return Returns the vertex coordinates
     */
    const Coordinates& getCoordinates() const;
    /**
     * @return Return the edge stored in path
     */
    const std::shared_ptr<Edge>& getPath() const;
    /**
     * @return Returns if the vertex is visited
     */
    bool isVisited() const;
    /**
     * @brief Sets the visited parameter
     *
     * @param cond Value to be set
     */
    void setVisited(bool cond);
    /**
     * @brief Sets the dist parameter
     *
     * @param distance Value to be set
     */
    void setDist(double distance);
    /**
     * @brief Sets the path parameter
     *
     * @param e Pointer to the edge to be set
     */
    void setPath(std::shared_ptr<Edge> e);
    /**
     * @brief Sets the in parameter
     *
     * @param value Value to be set
     */
    void setIn(uint32_t value);
    /**
     * @brief Sets the out parameter
     *
     * @param value Value to be set
     */
    void setOut(uint32_t value);
    /**
     * @brief Allows to add a edge with destination on the vertex and specified distance
     *
     * @param s Represents the source vertex of the edge
     * @param d Represents the destination vertex of the edge
     * @param distance Represents the distance of the Edge
     */
    void addEdge(const std::shared_ptr<Vertex> &s, const std::shared_ptr<Vertex>& d, double distance);
    /**
     * @brief Finds an edge
     *
     * @param d Destination vertex
     * @return Returns a pointer to the edge or nullptr if the edge does not exist
     */
    std::shared_ptr<Edge> findEdge(const std::shared_ptr<Vertex>& d) const;


    friend class MutablePriorityQueue<Vertex>;
protected:
    int queueIndex = 0; ///< Used in the mutable priority queue
};

/**
 * @brief Specifies how the vertex should be sorted
 *
 * @param a Pointer to a vertex
 * @param b Pointer to a vertex
 * @return True if a is less then b, False otherwise
 */
bool operator<(const Vertex& a, const Vertex& b);

#endif
