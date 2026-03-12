cmake_minimum_required(VERSION 3.30)
project(RBTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RBTree
    IODialog.h
    Main.cpp
    RBNode.h)
