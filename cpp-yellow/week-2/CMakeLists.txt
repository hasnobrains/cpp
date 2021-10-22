cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(MYENV)

# set the project name
project(week-2)

# add the executable
add_executable(bus1 bus1.cpp)
