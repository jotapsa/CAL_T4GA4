cmake_minimum_required(VERSION 3.10)
project(CAL_T4GA4)

set(CMAKE_CXX_STANDARD 11)

include_directories(project_part_1/src)

add_executable(CAL_T4GA4
        project_part_1/src/Connection.cpp
        project_part_1/src/Connection.h
        project_part_1/src/EdgeType.h
        project_part_1/src/GraphViewer.cpp
        project_part_1/src/GraphViewer.h
        project_part_1/src/main.cpp
        project_part_1/src/Graph.h
        project_part_1/src/MutablePriorityQueue.cpp
        project_part_1/src/MutablePriorityQueue.h
        project_part_1/src/Location.cpp
        project_part_1/src/Location.cpp
        project_part_1/src/Location.h
        project_part_1/src/Vertex.cpp
        project_part_1/src/Vertex.h
        project_part_1/src/Edge.cpp
        project_part_1/src/Edge.h
        project_part_1/src/Street.cpp
        project_part_1/src/Street.h
        project_part_1/src/Graph.cpp project_part_1/src/Cli.cpp project_part_1/src/Cli.h)
