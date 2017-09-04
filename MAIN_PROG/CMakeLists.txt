cmake_minimum_required(VERSION 3.7)
project(MAIN_PROG)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp 1.h 2.cpp)
add_executable(MAIN_PROG ${SOURCE_FILES})