cmake_minimum_required(VERSION 3.9)
project(Introsort)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        insertionsort.h
        introsort.h
        main.cpp
        sorting_networks.h
        tests/tests.h)
