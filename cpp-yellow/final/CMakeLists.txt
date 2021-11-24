cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-ggdb3 -g3")

add_compile_definitions(DEBUG)

# set the project name
project(final)

# add the executable
add_executable(inheritance inheritance.cpp)
