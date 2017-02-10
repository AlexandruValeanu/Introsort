cmake_minimum_required(VERSION 3.6)
project(IntroSort)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Insertionsort.h sorting_networks.h Introsort.h)
add_executable(IntroSort ${SOURCE_FILES} Insertionsort.h sorting_networks.h Introsort.h)
