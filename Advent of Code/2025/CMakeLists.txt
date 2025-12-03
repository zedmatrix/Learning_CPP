cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(advent_of_code VERSION 1.0)

include_directories(.)

add_executable(advent main.cpp)

#target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}")
