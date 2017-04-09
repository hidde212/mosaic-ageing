cmake_minimum_required(VERSION 3.6)
project(Project_fast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp globals.h globals.cpp randomnumbers.cpp randomnumbers.h)
add_executable(Project_fast ${SOURCE_FILES})