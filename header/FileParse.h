#ifndef DA_SECONDPROJECT_FILEPARSE_H
#define DA_SECONDPROJECT_FILEPARSE_H

#include "Graph.h"
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>

/**
 * @namespace FileParse
 * @brief Contains the functions used for parsing the files
 */
namespace FileParse{
    /**
     * @brief Responsible for reading and parsing all files
     *
     * @param g Pointer to the graph where the information will be stored
     * @param edges Name of the edges file
     * @param nodes Name of the nodes file
     * @param header True if the CSV file has an header, false otherwise
     * @param num_nodes Number of nodes to be read from the nodes file
     * @param path Name of the path being used
     * @param only_edges True if there is no nodes file, false otherwise
     * @return True if was able to open all files, false otherwise
     */
    bool readFiles(std::unique_ptr<Graph>& g, std::string& edges, std::string& nodes, bool header, uint32_t num_nodes, std::string& path, bool only_edges);
    /**
     * @brief Reads and parses the data from the nodes file
     *
     * @param g Pointer to the graph where the information will be stored
     * @param in File being read
     * @param num_nodes Number of nodes to be read from the nodes file
     * @param m Unordered map used to make the process of reading the files faster
     */
    void readNodes(std::unique_ptr<Graph>& g, std::ifstream& in, uint32_t num_nodes, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m);
    /**
     * @brief Reads and parses the data from the edges file
     *
     * @param g Pointer to the graph where the information will be stored
     * @param in File being read
     * @param header True if the CSV file has an header, false otherwise
     * @param m Unordered map used to make the process of reading the files faster
     */
    void readEdges(std::unique_ptr<Graph>& g, std::ifstream& in, bool header, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m);
    /**
     * @brief Reads and parses the data from the edges file
     *
     * @param g Pointer to the graph where the information will be stored
     * @param in File being read
     * @param header True if the CSV file has an header, false otherwise
     */
    void readOnlyEdges(std::unique_ptr<Graph>& g, std::ifstream& in, bool header);

}

#endif
