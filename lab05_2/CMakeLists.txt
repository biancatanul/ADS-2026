cmake_minimum_required(VERSION 3.30)
project(lab05_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lab05_2 main.cpp binomial_heap.h IODialog.h)