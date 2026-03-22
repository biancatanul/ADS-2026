cmake_minimum_required(VERSION 3.30)
project(lab04)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BTree.h
        IODialog.h
        Main.cpp)