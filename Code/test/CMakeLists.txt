cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
enable_testing()

find_package(GTest REQUIRED)

include_directories(../src/)
include_directories(${GTEST_INCLUDE_DIRS})

# add sort as test (see Chapter 2, 6, 7)
add_executable(sort-test sort_test.cpp)
target_link_libraries(sort-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(sort-test sort-lib)

# add data_structure as test
# 1. priority_deque (see Chapter 6)
add_executable(priority_deque-test priority_deque_test.cpp)
target_link_libraries(priority_deque-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(priority_deque-test data_structure-lib)
# 2. d_heap (see Chapter 6)
add_executable(d_heap-test d_heap_test.cpp)
target_link_libraries(d_heap-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(d_heap-test data_structure-lib)
# 3. binary_search_tree (see Chapter 12)
add_executable(binary_search_tree-test binary_search_tree_test.cpp)
target_link_libraries(binary_search_tree-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(binary_search_tree-test data_structure-lib)
# add them to AllTests
add_test(AllTests sort-test)
add_test(AllTests priority_deque-test)
add_test(AllTests d_heap-test)
