cmake_minimum_required(VERSION 3.30)
project(ADS_2026)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab01)
include_directories(lab02)
include_directories(lab03)
include_directories(lab04)

add_executable(lab01 lab01/main.cpp)

add_executable(lab02 lab02/Main.cpp)

add_executable(problem1 lab03/problem1.cpp)
add_executable(problem2 lab03/problem2.cpp)

add_executable(lab04 lab04/main.cpp)