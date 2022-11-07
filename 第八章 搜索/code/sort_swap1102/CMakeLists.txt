cmake_minimum_required(VERSION 3.17)
project(sort_swap1102)

set(CMAKE_CXX_STANDARD 14)

add_executable(sort_swap1102 main.cpp bubbling_sort.cpp sort.cpp sort.h heapsort.cpp heapsort.h merge.cpp merge.h)