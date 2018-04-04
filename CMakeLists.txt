cmake_minimum_required(VERSION 3.10)
project(CAL_T4GA4)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(CAL_T4GA4
        resources/arestas.txt
        resources/nos.txt
        src/Connection.cpp
        src/Connection.h
        src/Edge.cpp
        src/Edge.h
        src/EdgeType.h
        src/Graph.cpp
        src/Graph.h
        src/GraphViewer.cpp
        src/GraphViewer.h
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
