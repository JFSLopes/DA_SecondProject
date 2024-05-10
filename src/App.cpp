#include "../header/App.h"
#include "../header/UI.h"
#include "../header/FileParse.h"
#include <iostream>
#include <cfloat>
#include <memory>

void App::init() {
    while(true){
        g = std::make_unique<Graph>();
        std::string nodes;
        std::string edges;
        std::string path;
        bool header;
        bool edges_only;
        uint32_t num_nodes_file;

        displayChooseFiles(edges, nodes, header, num_nodes_file, path, edges_only);
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
    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();


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



    // End the timer
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration in seconds
    std::chrono::duration<double> duration = end_time - start_time;
    double duration_seconds = duration.count();

    // Output the time taken
    std::cout << "Time taken: " << duration_seconds << " seconds\n";
}

void App::triangular_approximation(){
    auto start_time = std::chrono::steady_clock::now(); // Record start time


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

    auto end_time = std::chrono::steady_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calculate duration
    double seconds = duration.count() / 1000.0; // Convert milliseconds to seconds
    std::cout << "Time taken: " << seconds << " seconds\n";
}

bool App::make_fully_connected() {
    if (num_nodes * (num_nodes - 1) == num_edges) return true;
    if (!g->getVertexSet().empty() and g->getVertexSet().front()->getCoordinates().getLat() == DBL_MAX) return false;
    g->fully_connected(num_edges);
    return (num_nodes * (num_nodes - 1) == num_edges);
}

void App::other_heuristic(){
    auto start_time = std::chrono::steady_clock::now(); // Record start time



    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    g->Christofides(s, hamiltonian);
    displayPath(hamiltonian);



    auto end_time = std::chrono::steady_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calculate duration
    double seconds = duration.count() / 1000.0; // Convert milliseconds to seconds
    std::cout << "Time taken: " << seconds << " seconds\n";
}

void App::nearest_neighbour() {
    auto start_time = std::chrono::steady_clock::now(); // Record start time


    std::shared_ptr<Vertex> s = g->findVertex(0);
    std::vector<std::shared_ptr<Edge>> hamiltonian;
    if (!make_fully_connected()){
        std::cout << "Is not possible to do the approximation\n";
        return;
    }
    g->nearest_neighbour(s, hamiltonian);
    displayPath(hamiltonian);



    auto end_time = std::chrono::steady_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calculate duration
    double seconds = duration.count() / 1000.0; // Convert milliseconds to seconds
    std::cout << "Time taken: " << seconds << " seconds\n";
}

void App::TSP_Real_World() const {

    std::vector<std::shared_ptr<Edge>> hamiltonian;
    std::shared_ptr<Vertex> s = ask_vertex(g);
    if (!g->nearest_neighbour(s, hamiltonian)){
        std::cout << "No path found.\n";
    }
    else displayPath(hamiltonian);
}