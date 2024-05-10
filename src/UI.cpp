#include "../header/UI.h"
#include <iostream>
#include <iomanip>

std::string getNewPath(){
    std::cout << "Enter the new Path. Keep in mind that either the path is absolute or, if relative, it is in relation to where the executable is.\n";
    std::string newPath;
    std::getline(std::cin, newPath);
    return newPath;
}
std::string getNewFileName(const std::string& name){
    std::cout << "Enter the file name for the " << name << " file.\n";
    std::string newFile;
    std::getline(std::cin, newFile);
    return newFile;
}

char getYesNoAnswer(){
    std::cout << "[y/n]: ";
    do{
        std::string value;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(value.size() == 1 and (value[0] == 'y' or value[0] == 'n')) return value[0] == 'y';
        else{
            std::cout << "Invalid input, enter either 'y' or 'n': ";
        }
    } while (true);
}

uint32_t askNumber(uint32_t upperLimit){
    do{
        try {
            std::string value;
            std::cin >> value;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            uint32_t number = std::stoi(value);

            if (number <= upperLimit) {
                return number;
            } else {
                std::cout << "Invalid input. The number must be between 0 and " << upperLimit << ": ";
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid number: ";
        } catch (const std::out_of_range& e) {
            std::cout << "Input out of range. Please enter a valid number: ";
        }
    } while (true);
}

void displayChooseFiles(std::string& edges, std::string& nodes, bool& header, uint32_t& num_nodes, std::string& path, bool& edges_only){
    std::cout << "Does it exist a nodes file?\n";
    edges_only = !getYesNoAnswer();
    if (edges_only){
        edges = getNewFileName("Edges");
        std::cout << "Does the file " << edges << " has a header?\n";
        header = getYesNoAnswer();
    }
    else{
        nodes = getNewFileName("nodes");
        std::cout << "How many nodes are in the file: ";
        num_nodes = askNumber(UINT32_MAX);
        edges = getNewFileName("Edges");
        std::cout << "Does the file " << edges << " has a header?\n";
        header = getYesNoAnswer();
    }

    std::cout << "Are the files in the same folder where the executable is?\n";
    bool answer = getYesNoAnswer();
    if (!answer){
        path = getNewPath();
        if (!path.empty() and path.back() != '/') path += "/";
    }
}

void displayFunctionalities(){
    std::cout << "Choose one of the following options:\n"
              << "\t1. Backtracking algorithm;\n"
              << "\t2. Triangular Approximation Heuristic;\n"
              << "\t3. Other Heuristics (Christofides);\n"
              << "\t4. Other Heuristics (Nearest neighbour);\n"
              << "\t5. TSP in the Real World;\n"
              << "\t8. Load other files.\n"
              << "\t9. Close the app.\n";
    std::cout << "[1..9]: ";
}

void displayPath(const std::vector<std::shared_ptr<Edge>>& path){
    std::cout << "The following Hamiltonian path was found:\n";
    double dist = 0;
    std::cout << path.front()->getOrig()->getCode() << " - ";
    for (const std::shared_ptr<Edge>& e : path){
        std::cout << e->getDest()->getCode();
        if (e->getDest()->getCode() != path.front()->getOrig()->getCode()) std::cout << " - ";
        dist += e->getWeight();
    }
    std::cout << "\nThe total distance is: " << std::fixed << std::setprecision(2) << dist << "\n";
}

std::shared_ptr<Vertex> ask_vertex(const std::unique_ptr<Graph>& g){
    std::cout << "Enter the source vertex index: ";
    while (true){
        uint32_t index = askNumber(UINT32_MAX);
        std::shared_ptr<Vertex> v = g->findVertex(index);
        if (v == nullptr){
            std::cout << "Invalid index. The vertex does not exist. Enter a valid one: ";
            continue;
        }
        return v;
    }
}