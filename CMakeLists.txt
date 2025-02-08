cmake_minimum_required(VERSION 3.10)
project(TDMATRIX)
set(CMAKE_CXX_STANDARD 20)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})



add_executable(TDMATRIX src/test.cpp
        src/test.cpp
        src/TDMatrix.h)
target_link_libraries(TDMATRIX ${GTEST_LIBRARIES} pthread)