cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-ggdb3 -g3")

add_compile_definitions(MYENV)

# set the project name
project(week-4)

# add the executable
add_executable(print_vector_part print_vector_part.cpp)
add_executable(find_greater_elements find_greater_elements.cpp)
add_executable(split_into_words split_into_words.cpp)
add_executable(remove_duplicates remove_duplicates.cpp)
add_executable(print_permutations print_permutations.cpp)
add_executable(print_stats print_stats.cpp)
add_executable(merge_sort_div2 merge_sort_div2.cpp)
add_executable(merge_sort_div3 merge_sort_div3.cpp)
add_executable(budget_starter budget_starter.cpp)
add_executable(budget_starter_plus budget_starter_plus.cpp)
