cmake_minimum_required(VERSION 3.9)
project(Introsort)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Introsort)

add_executable(
        Insertionsort.h
        insertionsort.h
        Introsort.h
        introsort.h
        main.cpp
        sorting_networks.h
        tests.h)
