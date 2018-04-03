cmake_minimum_required(VERSION 3.10)
project(project_part_1)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(project_part_1
        resources/arestas.txt
        resources/nos.txt
        src/connection.cpp
        src/connection.h
        src/Edge.cpp
        src/Edge.h
        src/edgetype.h
        src/Graph.cpp
        src/Graph.h
        src/graphviewer.cpp
        src/graphviewer.h
        src/Location.cpp
        src/Location.h
        src/Location.h
        src/MutablePriorityQueue.cpp
        src/MutablePriorityQueue.h
        src/Street.cpp
        src/Street.h
        src/Vertex.cpp
        src/Vertex.h
        src/main.cpp
        GraphViewerController.jar)
