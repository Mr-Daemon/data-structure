cmake_minimum_required(VERSION 3.10)
project(data_structure)

set(CMAKE_CXX_STANDARD 11)

add_executable(test_file abstract_structure/test_file.cpp abstract_structure/ArrayList.h abstract_structure/huffman_encode.cpp abstract_structure/huffman_encode.h abstract_structure/huffman_tree.h abstract_structure/List.h abstract_structure/Graph.h abstract_structure/AdjacencyWDigraph.h)
add_executable(main test_use/main.cpp)

add_subdirectory(factory_simulate)
add_subdirectory(search)
add_executable(matrix old_version/matrix.cpp)

add_executable(dynamic_search search/dynamic_search.cpp)
add_executable(avl_tree search/avl_tree.cpp)
add_executable(max_heap search/max_heap.cpp)
add_executable(hblt search/hblt.cpp)
add_executable(insert_sort sort/insert_sort.cpp)
add_executable(swap_sort sort/swap_sort.cpp)
add_executable(select_sort sort/select_sort.cpp)
add_executable(merge_sort sort/merge_sort.cpp)