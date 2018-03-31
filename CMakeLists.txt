cmake_minimum_required(VERSION 3.10)
project(CAL_T4GA4)

set(CMAKE_CXX_STANDARD 11)

include_directories(project_part_1/src)

add_executable(CAL_T4GA4
        project_part_1/src/connection.cpp
        project_part_1/src/connection.h
        project_part_1/src/edgetype.h
        project_part_1/src/graphviewer.cpp
        project_part_1/src/graphviewer.h
        project_part_1/src/main.cpp project_part_1/src/Vertex.cpp project_part_1/src/Vertex.h)
