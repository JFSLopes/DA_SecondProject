#include "../header/UI.h"
#include <iostream>

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
        std::string value;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(value.size() == 1 and value.front() >= '1' and value.front() <= '0' + upperLimit){
            return value[0] - '0';
        }
        else std::cout << "Invalid input. The number must be between 1 and " << upperLimit << ": ";
    } while (true);
}

void displayChooseFiles(std::string& edges, std::string& nodes, bool& header, std::string& path){
    nodes = getNewFileName("nodes");
    edges = getNewFileName("Edges");
    std::cout << "Does the file " << edges << "has a header?\n";
    header = getYesNoAnswer();

    std::cout << "Are the files in the same folder where the executable is?\n";
    bool answer = getYesNoAnswer();
    if (!answer){
        path = getNewPath();
        if (!path.empty() and path.back() != '/') path += "/";
    }
}

void displayFunctionalities(){
    std::cout << "Choose one of the following options:\n"
              << "\t1. ;\n"
              << "\t2. ;\n"
              << "\t8. Load other files.\n"
              << "\t9. Close the app.\n";
    std::cout << "[1..9]: ";
}