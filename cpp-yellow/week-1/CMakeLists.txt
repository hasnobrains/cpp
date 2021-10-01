cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(MYENV)

# set the project name
project(week-1)

# add the executable
add_executable(matrix matrix.cpp)
add_executable(temperature temperature.cpp)
add_executable(block_weight block_weight.cpp)
add_executable(find_max_repetition_count find_max_repetition_count.cpp)
add_executable(team_tasks team_tasks.cpp)
