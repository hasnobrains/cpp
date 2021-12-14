cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_compile_definitions(DEBUG)

# set the project name
project(week-1)

# add the executable
add_executable(update_field update_field.cpp)
add_executable(print_values print_values.cpp)
add_executable(uniq_id uniq_id.cpp)
add_executable(table table.cpp)
add_executable(deque deque.cpp)
