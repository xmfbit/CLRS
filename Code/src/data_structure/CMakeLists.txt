cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_library(data_structure-lib STATIC priority_deque.hpp d_heap.hpp binary_search_tree.hpp rb_tree.hpp)
SET_TARGET_PROPERTIES(data_structure-lib PROPERTIES LINKER_LANGUAGE CXX)
