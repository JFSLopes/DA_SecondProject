#ifndef DA_SECONDPROJECT_EDGE_H
#define DA_SECONDPROJECT_EDGE_H

class Vertex;

#include "Vertex.h"
#include <memory>

/**
 * @class Edge
 * @brief Allows to represent the information of any edge on the graph
 */
class Edge {
private:
    std::shared_ptr<Vertex> orig; ///< Represents the destination Vertex of the edge
    std::shared_ptr<Vertex> dest; ///< Represents the destination Vertex of the edge
    double weight; ///< Represents the weight of the edge
    bool selected; ///< Represents if the edge was selected during an algorithm
public:
    /**
     * @brief Edge Constructor
     * @param orig Origin Vertex of the edge
     * @param dest Destination Vertex of the edge
     * @param weight Weight of the edge
     */
    Edge(std::shared_ptr<Vertex> orig, std::shared_ptr<Vertex> dest, double weight);
    /**
     * @return Returns the destination Vertex of the Edge
     */
    std::shared_ptr<Vertex> getDest() const;
    /**
    * @return Returns the origin Vertex of the Edge
    */
    std::shared_ptr<Vertex> getOrig() const;
    /**
     * @return Returns the weight of the Edge
     */
    double getWeight() const;
    /**
     * @return Returns if the edge is selected
     */
    bool isSelected() const;
    /**
     * @brief Allows to change the selected parameter
     * @param cond Value to be put in selected
     */
    void setSelected(bool cond);
};

#endif
