#include "../header/FileParse.h"
#include "../header/UI.h"
#include <iostream>
#include <sstream>

bool FileParse::readFiles(std::unique_ptr<Graph> &g, std::string &edges, std::string &nodes, bool header, uint32_t num_nodes, std::string &path, bool only_edges){
    if (only_edges){
        std::ifstream edges_file(path + edges);
        if (!edges_file.is_open()){
            std::cout << "Unable to open file: " << edges << "\n";
            return false;
        }
        FileParse::readOnlyEdges(g, edges_file, header);
        return true;
    }
    /// Try to open files
    std::ifstream nodes_file(path + nodes);
    if (!nodes_file.is_open()){
        std::cout << "Unable to open file: " << nodes << "\n";
        return false;
    }

    std::ifstream edges_file(path + edges);
    if (!edges_file.is_open()){
        std::cout << "Unable to open file: " << edges << "\n";
        return false;
    }
    std::unordered_map<uint32_t, std::shared_ptr<Vertex>> m;
    FileParse::readNodes(g, nodes_file, num_nodes, m);
    FileParse::readEdges(g, edges_file, header, m);
    return true;
}

void FileParse::readNodes(std::unique_ptr<Graph> &g, std::ifstream &in, uint32_t num_nodes, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m) {
    std::string line;
    /// Skip the header
    std::getline(in, line);
    while(num_nodes-- and std::getline(in, line)){
        std::istringstream aux(line);
        std::string id, longitude, latitude;

        std::getline(aux, id, ',');
        std::getline(aux, longitude, ',');
        std::getline(aux, latitude);

        uint32_t ID = std::stoi(id);
        double lon = std::stod(longitude);
        double lat = std::stod(latitude);

        std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(ID, lon, lat);
        g->addVertex(vertex);
        m.insert(std::make_pair(ID, vertex));
    }
}

void FileParse::readEdges(std::unique_ptr<Graph> &g, std::ifstream &in, bool header, std::unordered_map<uint32_t, std::shared_ptr<Vertex>>& m) {
    std::string line;
    if (header){
        /// Skip the header
        std::getline(in, line);
    }
    std::shared_ptr<Vertex> prevOrig;
    std::shared_ptr<Vertex> prevDest;
    while (std::getline(in, line)){
        std::istringstream aux(line);
        std::string origen, destination, distance;

        std::getline(aux, origen, ',');
        std::getline(aux, destination, ',');
        std::getline(aux, distance);

        uint32_t orig = std::stoi(origen);
        uint32_t dest = std::stoi(destination);
        double dist = std::stod(distance);

        if (prevOrig == nullptr or prevOrig->getCode() != orig){
            prevOrig = m.find(orig)->second;
        }
        if (prevDest == nullptr or prevDest->getCode() != dest){
            prevDest = m.find(dest)->second;
        }

        prevOrig->addEdge(prevOrig, prevDest, dist);
        prevDest->addEdge(prevDest, prevOrig, dist);
    }
}

void FileParse::readOnlyEdges(std::unique_ptr<Graph> &g, std::ifstream &in, bool header) {
    std::string line;
    if (header){
        std::getline(in, line);
    }

    while(std::getline(in, line)){
        std::istringstream aux(line);
        std::string origen, destination, distance;

        std::getline(aux, origen, ',');
        std::getline(aux, destination, ',');
        std::getline(aux, distance);

        uint32_t orig = std::stoi(origen);
        uint32_t dest = std::stoi(destination);
        double dist = std::stod(distance);

        std::shared_ptr<Vertex> s = g->findVertex(orig);
        std::shared_ptr<Vertex> d = g->findVertex(dest);

        if (s == nullptr){
            s = std::make_shared<Vertex>(orig, 0, 0);
            g->addVertex(s);
        }

        if (d == nullptr){
            d = std::make_shared<Vertex>(dest, 0, 0);
            g->addVertex(d);
        }

        s->addEdge(s, d, dist);
        d->addEdge(d, s, dist);
    }
}