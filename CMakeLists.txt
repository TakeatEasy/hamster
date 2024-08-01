cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(hamster)

# find_package(Torch REQUIRED)
# message("Found torch")
# add_executable(dcgan test.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE CSRC_CPP ${CMAKE_CURRENT_SOURCE_DIR}/csrc/*.cpp)
message("All cscr cpp file:" ${CSRC_CPP})

add_library(hamster SHARED ${CSRC_CPP})