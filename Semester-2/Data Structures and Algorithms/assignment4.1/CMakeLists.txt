cmake_minimum_required(VERSION 3.24)
project(assignment4)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(assignment4
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMIterator.cpp
        SMIterator.h
        SortedMap.cpp
        SortedMap.h)
