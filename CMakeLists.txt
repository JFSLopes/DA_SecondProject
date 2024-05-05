cmake_minimum_required(VERSION 3.28)
project(DA_SecondProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_SecondProject main.cpp
        src/FileParse.cpp
        src/Graph.cpp
        src/UI.cpp
        src/Vertex.cpp
        src/Edge.cpp
        src/App.cpp
        src/Coordinates.cpp)
