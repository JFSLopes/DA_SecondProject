#ifndef DA_SECONDPROJECT_FILEPARSE_H
#define DA_SECONDPROJECT_FILEPARSE_H

#include "Graph.h"
#include <string>
#include <fstream>
#include <map>

namespace FileParse{
    bool readFiles(std::unique_ptr<Graph>& g, std::string& edges, std::string& nodes, bool header, uint32_t num_nodes, std::string& path, bool only_edges);
    void readNodes(std::unique_ptr<Graph>& g, std::ifstream& in, uint32_t num_nodes, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m);
    void readEdges(std::unique_ptr<Graph>& g, std::ifstream& in, bool header, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m);
    void readOnlyEdges(std::unique_ptr<Graph>& g, std::ifstream& in, bool header);

}

#endif
