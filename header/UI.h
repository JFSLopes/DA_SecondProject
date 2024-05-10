#ifndef DA_SECONDPROJECT_UI_H
#define DA_SECONDPROJECT_UI_H

class Edge;

#include "Edge.h"
#include "Graph.h"
#include <string>
#include <memory>

/**
 * @return Returns a string with the path of a file
 */
std::string getNewPath();
/**
 *
 * @param name String used to name the file
 * @return Returns the name of the file
 */
std::string getNewFileName(const std::string& name);
/**
 * @brief Reads the answer from the user to a yes or no question and checks if it is valid
 *
 * @return Returns the character associated to the answer
 */
char getYesNoAnswer();
/**
 * @brief Reads a number from the user and checks if it is invalid
 *
 * @param upperLimit maximum value that can be read
 * @return Returns the number that was insert by the user
 */
uint32_t askNumber(uint32_t upperLimit);

void displayChooseFiles(std::string& edges, std::string& nodes, bool& header, uint32_t& num_nodes, std::string& path, bool& edges_only);
void displayFunctionalities();
void displayPath(const std::vector<std::shared_ptr<Edge>>& path);
std::shared_ptr<Vertex> ask_vertex(const std::unique_ptr<Graph>& g);

#endif
