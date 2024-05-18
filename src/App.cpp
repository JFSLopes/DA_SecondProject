#include "../header/App.h"
#include "../header/UI.h"
#include "../header/FileParse.h"
#include <iostream>
#include <cfloat>
#include <memory>

void App::init() {
    while(true){
        g = std::make_unique<Graph>();
        nodes = "nodes.csv";
        edges = "edges.csv";
        path = "../Dataset/Real-world/graph3/";
        header = true;
        edges_only = false;
        num_nodes_file = 10000;

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
                if (made_fully_connected){
                    std::cout << "Reverting the changes made to the graph in previous algorithms.\n";
                    g = std::make_unique<Graph>();
                    made_fully_connected = false;
                    if (FileParse::readFiles(g, edges, nodes, header, num_nodes_file, path, edges_only)){
                        std::cout << "Previous changes were successfully reverted.\n";
                    }
                    else{
                        std::cout << "Something went wrong while reverting the changes.\n";
                        continue;
                    }
                }
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
        std::cout << "Press Enter to continue";
        std::string aux;
        std::getline(std::cin, aux);
        std::cout << "\n\n";
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
    std::cout << "Running the backtracking algorithm.\n";
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
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "The algorithm will run on a graph that is not fully connected due to missing information.\n";
    }
    std::cout << "Running the Triangular algorithm.\n";
    if (!g->triangular_approximation(s, hamiltonian)){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    displayPath(hamiltonian);
}

bool App::make_fully_connected() {
    if (num_nodes * (num_nodes - 1) == num_edges) return true;
    if (!g->getVertexSet().empty() and g->getVertexSet().front()->getCoordinates().getLat() == DBL_MAX) return false;
    std::cout << "Making the graph fully connected...\n";
    g->fully_connected(num_edges);
    made_fully_connected = true;
    return (num_nodes * (num_nodes - 1) == num_edges);
}

void App::other_heuristic(){
    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "The algorithm will run on a graph that is not fully connected due to missing information.\n";
    }
    std::cout << "Running the Christofides algorithm.\n";
    if (!g->Christofides(s, hamiltonian)){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    displayPath(hamiltonian);
}

void App::nearest_neighbour() {
    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "The algorithm will run on a graph that is not fully connected due to missing information.\n";
    }
    std::cout << "Running the NN algorithm.\n";
    if (!g->nearest_neighbour(s, hamiltonian)){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    displayPath(hamiltonian);
}

void App::TSP_Real_World() const {
    std::shared_ptr<Vertex> s = ask_vertex(g);
    std::vector<std::shared_ptr<Vertex>> hamiltonian;
    std::cout << "Running the real-world algorithm algorithm.\n";
    if (!g->nn_with_backtracking(s, hamiltonian)){
        std::cout << "No path found.\n";
        return;
    }
    std::cout << "A hamiltonian path was found. Do you pretend to tru to improve it with a 2-opt algorithm?\n";
    bool answer = getYesNoAnswer();
    std::cout << "How many iteration you want to execute?\n";
    uint32_t num_iterations = askNumber(UINT32_MAX);

    double dist = 0;
    for (uint32_t k = 0; k < hamiltonian.size() - 1; k++){
        std::shared_ptr<Edge> e = hamiltonian[k]->findEdge(hamiltonian[k+1]);
        dist += e->getWeight();
    }

    if (answer){
        std::cout << "Running the 2-opt algorithm.\n";
        g->opt2(hamiltonian, dist, num_iterations);
    }
    displayPath(hamiltonian);
}