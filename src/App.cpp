#include "../header/App.h"
#include "../header/UI.h"
#include "../header/FileParse.h"
#include <iostream>

void App::init() {
    while(true){
        std::string nodes = "nodes.csv";
        std::string edges = "edges_900.csv";
        std::string path = "../Dataset/Fully-connected/";
        bool header = true;
        uint32_t num_nodes = 900;
        g = std::make_unique<Graph>();


        // Start measuring time
        auto startTime = std::chrono::high_resolution_clock::now();


        //displayChooseFiles(edges, nodes, header, num_nodes, path);
        if (!FileParse::readFiles(g, edges, nodes, header, num_nodes, path)){
            std::cout << "Something went wrong while reading the files. Make sure the names and path are correct.\n";
            continue;
        }


        auto endTime = std::chrono::high_resolution_clock::now();
        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Time taken by FileParse::readFiles: " << duration << " milliseconds\n";



        //bool answer = functionalities();
        //if (answer) break;
        break;
    }
}

bool App::functionalities() {
    std::vector<std::shared_ptr<Vertex>> vec = g->getVertexSet();
    std::cout << "Number of vertex: " << vec.size() << "\n";
    int count = 0;
    for (const auto& x : vec){
        for (auto y : x->getAdj()){
            std::cout << x->getCode() << " " << y->getDest()->getCode() << "\n";
            count++;
        }
    }
    std::cout << "Number of edges: " << count << "\n";
    return true;
}