cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the project name
project(week-1)

# add the executable
add_executable(matrix matrix.cpp)
add_executable(temperature temperature.cpp)
add_executable(block_weight block_weight.cpp)

