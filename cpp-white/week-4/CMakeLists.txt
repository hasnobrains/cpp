cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the project name
project(week-4)

# add the executable
add_executable(invertible_function_test invertible_function_test.cpp)
add_executable(invertible_function_test2 invertible_function_test2.cpp)
add_executable(input input.cpp)
add_executable(input2 input2.cpp)
add_executable(input3 input3.cpp)
add_executable(input4 input4.cpp)
add_executable(students students.cpp)
add_executable(rational_interface rational_interface.cpp)
add_executable(rational_eq_add_sub rational_eq_add_sub.cpp)
add_executable(rational_mult_div rational_mult_div.cpp)
add_executable(rational_io rational_io.cpp)
add_executable(rational_map rational_map.cpp)
add_executable(ensure_equal ensure_equal.cpp)
add_executable(rational_throw rational_throw.cpp)
add_executable(rational_calc rational_calc.cpp)
add_executable(time_server time_server.cpp)

