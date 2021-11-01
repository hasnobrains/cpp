cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-ggdb3 -g3")

add_compile_definitions(MYENV)

# set the project name
project(week-2)

# add the executable
add_executable(bus1 bus1.cpp)
add_executable(test_equation test_equation.cpp)
add_executable(test_person test_person.cpp)
add_executable(test_rational test_rational.cpp)
add_executable(test_palindrome test_palindrome.cpp)
add_executable(test_sum_reverse_sort sum_reverse_sort.cpp
    sum_reverse_sort_test.cpp)
add_executable(test_phone_number phone_number.cpp phone_number_test.cpp)
add_executable(bus main.cpp bus_manager.cpp query.cpp responses.cpp)
