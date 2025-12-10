cmake_minimum_required(VERSION 3.14)
project(CPP_Plot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Matplot++ as a subdirectory
add_subdirectory(external/matplotplusplus/source)

# Executable 1: line
add_executable(line line.cpp)
target_link_libraries(line PRIVATE Matplot++::matplot)

# Executable 2: line
add_executable(histogram histogram.cpp)
target_link_libraries(histogram PRIVATE Matplot++::matplot)