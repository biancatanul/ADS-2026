cmake_minimum_required(VERSION 3.30)
project(lab05)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lab05 main.cpp heap.h IODialog.h)