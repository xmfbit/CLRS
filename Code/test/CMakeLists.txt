cmake_minimum_required(VERSION 2.8)
enable_testing()

find_package(GTest REQUIRED)

include_directories(../src/)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(sort-test sort_test.cpp)
target_link_libraries(sort-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(sort-test sort-lib)

add_test(AllTests sort-test)
