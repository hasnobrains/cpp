cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_compile_definitions(DEBUG)

# set the project name
project(week-2)

# add the executable
add_executable(sort_students sort_students.cpp)
add_executable(learner learner.cpp)
add_executable(slow_express slow_express.cpp)
add_executable(ebook ebook.cpp)
