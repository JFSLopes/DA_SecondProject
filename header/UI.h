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
/**
 * @brief Allows the user to select the files he will used along with some useful information
 *
 * @param edges Name of the edges file
 * @param nodes Name of the nodes file
 * @param header If the files have an header
 * @param num_nodes Number of the nodes the nodes' file has
 * @param path Path where the files are
 * @param edges_only Stores if there is only an edges' file
 */
void displayChooseFiles(std::string& edges, std::string& nodes, bool& header, uint32_t& num_nodes, std::string& path, bool& edges_only);
/**
 * @brief Displays the app functionalities
 */
void displayFunctionalities();
/**
 * @brief Displays the path found along with its distance
 *
 * @param path Path to be displayed
 */
void displayPath(const std::vector<std::shared_ptr<Edge>>& path);
/**
 * @brief Displays the path found along with its distance
 *
 * @param path Path to be displayed
 */
void displayPath(const std::vector<std::shared_ptr<Vertex>>& path);
/**
 * @brief Asks the user a vertex
 *
 * @param g Pointer to the graph
 * @return Returns a pointer to the choosen vertex
 */
std::shared_ptr<Vertex> ask_vertex(const std::unique_ptr<Graph>& g);

#endif
