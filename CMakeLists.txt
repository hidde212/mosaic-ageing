cmake_minimum_required(VERSION 3.6)
project(Mosaic_Ageing)

find_package(Boost )

find_package(Boost 1.55.0 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp globals.cpp globals.h randomnumbers.cpp randomnumbers.h individual.cpp individual.h population.cpp population.h)
add_executable(Mosaic_Ageing ${SOURCE_FILES})