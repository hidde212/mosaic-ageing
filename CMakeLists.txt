cmake_minimum_required(VERSION 3.6)
project(Mosaic_Ageing)

find_package(Boost 1.55.0 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp globals.h randomnumbers.cpp randomnumbers.h individual.h population.cpp population.h)
add_executable(Mosaic_Ageing ${SOURCE_FILES})