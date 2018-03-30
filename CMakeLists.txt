cmake_minimum_required(VERSION 3.6)   # CMake version check
project(CAL_T4GA4)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

set(SOURCE_FILES ./project_part_1/src/main.cpp ./project_part_1/src/graphviewer.cpp ./project_part_1/src/connection.cpp)            # Add main.cpp file of project root directory as source file
add_executable(CAL_T4GA4 ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable