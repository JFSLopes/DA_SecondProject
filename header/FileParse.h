#ifndef DA_SECONDPROJECT_FILEPARSE_H
#define DA_SECONDPROJECT_FILEPARSE_H

#include "Graph.h"
#include <string>
#include <fstream>

namespace FileParse{
    bool readFiles(std::unique_ptr<Graph>& g, std::string& edges, std::string& nodes, bool header, uint32_t num_nodes, std::string& path);
    void readNodes(std::unique_ptr<Graph>& g, std::ifstream& in,  uint32_t num_nodes);
    void readEdges(std::unique_ptr<Graph>& g, std::ifstream& in, bool header);
}

#endif
