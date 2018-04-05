cmake_minimum_required(VERSION 3.10)
project(CAL_T4GA4)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(CAL_T4GA4
        src/main.cpp
        src/Parser.cpp
        src/Parser.h
        src/GarbageManagement.cpp
        src/GarbageManagement.h
        src/Container.cpp
        src/Container.h
        src/Aux.cpp
        src/Aux.h
        src/Edge.h
        src/Connection.cpp
        src/Connection.h
        src/Graph.h
        src/GraphViewer.cpp
        src/GraphViewer.h
        src/Street.cpp
        src/Street.h
        src/Node.h
        src/Cli.cpp
        src/Cli.h
        GraphViewerController.jar
        src/Place.cpp
        src/Place.h
        src/Vehicle.cpp
        src/Vehicle.h
        src/Station.cpp
        src/Station.h
        src/Garage.cpp
        src/Garage.h)
