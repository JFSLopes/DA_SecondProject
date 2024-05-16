#include "../header/App.h"
#include "../header/UI.h"
#include "../header/FileParse.h"
#include <iostream>
#include <cfloat>
#include <memory>

void App::init() {
    while(true){
        g = std::make_unique<Graph>();
        std::string nodes = "nodes.csv";
        std::string edges = "edges.csv";
        std::string path = "../Dataset/Real-world/graph1/";
        bool header = true;
        bool edges_only = false;
        uint32_t num_nodes_file = 5000;

        //displayChooseFiles(edges, nodes, header, num_nodes_file, path, edges_only);
        if (!FileParse::readFiles(g, edges, nodes, header, num_nodes_file, path, edges_only)){
            std::cout << "Something went wrong while reading the files. Make sure the names and path are correct.\n";
            continue;
        }

        bool stay = functionalities();
        if (!stay) break;
    }
}

bool App::functionalities() {
    num_nodes = 0;
    num_edges = 0;
    num_nodes = g->getVertexSet().size();
    for (const std::shared_ptr<Vertex>& v : g->getVertexSet()){
        num_edges += v->getAdj().size();
    }
    std::cout << "Number of vertex: " << num_nodes << "\n";
    std::cout << "Number of edges: " << num_edges << "\n";

    while (true){
        displayFunctionalities();
        switch(askNumber(9)){
            case 1:
                backtracking();
                break;
            case 2:
                triangular_approximation();
                break;
            case 3:
                other_heuristic();
                break;
            case 4:
                nearest_neighbour();
                break;
            case 5:
                TSP_Real_World();
                break;
            case 8:
                return true;
            case 9:
                return false;
            default:
                std::cout << "Invalid input.\n";
                break;
        }
    }
}

void App::find_best_hamiltonian(
        std::shared_ptr<Vertex>& s,
        std::shared_ptr<Vertex>& d,
        std::vector<std::shared_ptr<Edge>>& curr_path,
        std::vector<std::shared_ptr<Edge>>& best_path,
        uint32_t size_hamiltonian,
        double& path_sum,
        double& best_sum) const{
    if (path_sum >= best_sum){ /// Bounding function
        return;
    }
    s->setVisited(true);

    for (const std::shared_ptr<Edge>& e : s->getAdj()){
        std::shared_ptr<Vertex> orig = e->getOrig();
        std::shared_ptr<Vertex> dest = e->getDest();
        if (!dest->isVisited()){
            curr_path.push_back(e);
            path_sum += e->getWeight();
            find_best_hamiltonian(dest, d, curr_path, best_path, size_hamiltonian, path_sum, best_sum);
            path_sum -= e->getWeight();
            curr_path.pop_back();
        }
        else if ( /** it is visited */ dest->getCode() == d->getCode() and curr_path.size() + 1 == size_hamiltonian){ /// It is a hamiltonian cycle
            curr_path.push_back(e);
            path_sum += e->getWeight();
            if (best_path.empty() or best_sum > path_sum){
                best_sum = path_sum;
                best_path = curr_path;
            }
            path_sum -= e->getWeight();
            curr_path.pop_back(); /// This must be explicitly removed here, otherwise the insert and remove on the curr_path would become desynchronized
        }
    }
    s->setVisited(false);
}

void App::backtracking() const {
    uint32_t size_hamiltonian = g->getVertexSet().size();
    for (const std::shared_ptr<Vertex>& vertex : g->getVertexSet()){
        vertex->setVisited(false);
    }

    std::vector<std::shared_ptr<Edge>> curr_path;
    std::vector<std::shared_ptr<Edge>> best_path;
    std::shared_ptr<Vertex> s = g->findVertex(0);
    s->setDist(0);
    double path_sum = 0, best_sum = DBL_MAX;
    find_best_hamiltonian(s, s, curr_path, best_path, size_hamiltonian, path_sum, best_sum);
    displayPath(best_path);
}

void App::triangular_approximation(){
    for (const std::shared_ptr<Vertex>& vertex : g->getVertexSet()){
        vertex->setVisited(false);
    }
    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> path;
    if (!make_fully_connected()){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    if (!g->triangular_approximation(s, path)){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    displayPath(path);
}

bool App::make_fully_connected() {
    if (num_nodes * (num_nodes - 1) == num_edges) return true;
    if (!g->getVertexSet().empty() and g->getVertexSet().front()->getCoordinates().getLat() == DBL_MAX) return false;
    g->fully_connected(num_edges);
    return (num_nodes * (num_nodes - 1) == num_edges);
}

void App::other_heuristic(){
    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    g->Christofides(s, hamiltonian);
    displayPath(hamiltonian);
}

void App::nearest_neighbour() {
    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    g->nearest_neighbour(s, hamiltonian);
    displayPath(hamiltonian);
}

void App::TSP_Real_World() const {

    std::vector<std::shared_ptr<Edge>> hamiltonian;
    std::shared_ptr<Vertex> s = ask_vertex(g);
    std::cout << "NN\n";
    if (!g->nearest_neighbour(s, hamiltonian)){
        std::cout << "No path found.\n";
    }
    else displayPath(hamiltonian);
    hamiltonian.clear();
    std::cout << "\nChristofides\n";
    if (!g->Christofides(s, hamiltonian)){
        std::cout << "No path found.\n";
    }
    else displayPath(hamiltonian);
    hamiltonian.clear();
    std::cout << "\nTriangular\n";
    if (!g->triangular_approximation(s, hamiltonian)){
        std::cout << "No path found.\n";
    }
    else displayPath(hamiltonian);
    hamiltonian.clear();
    std::vector<std::shared_ptr<Vertex>> path;
    std::cout << "\nNN->Backtracking\n";
    if (!g->nn_with_backtracking(s, path)){
        std::cout << "No path found.\n";
    }
    else displayPath(path);
}