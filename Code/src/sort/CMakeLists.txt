cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_library(sort-lib STATIC insertion_sort.hpp select_sort.hpp bubble_sort.hpp merge_sort.hpp heap_sort.hpp quick_sort.hpp counting_sort.hpp)
SET_TARGET_PROPERTIES(sort-lib PROPERTIES LINKER_LANGUAGE CXX)
