cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)

add_executable(lab1 main.cpp Graph.cpp Graph.h UI.cpp UI.h)
