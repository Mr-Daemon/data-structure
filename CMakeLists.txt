cmake_minimum_required(VERSION 3.10)
project(data_structure)

set(CMAKE_CXX_STANDARD 11)

add_executable(test_file abstract_structure/test_file.cpp abstract_structure/ArrayList.h abstract_structure/huffman_encode.cpp abstract_structure/huffman_encode.h abstract_structure/huffman_tree.h abstract_structure/List.h abstract_structure/Graph.h abstract_structure/AdjacencyWDigraph.h)
add_executable(main test_use/main.cpp)

add_subdirectory(factory_simulate)