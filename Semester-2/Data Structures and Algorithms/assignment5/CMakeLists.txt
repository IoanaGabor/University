cmake_minimum_required(VERSION 3.24)
project(assignment5)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(assignment5
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
