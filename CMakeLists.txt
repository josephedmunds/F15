cmake_minimum_required(VERSION 3.3)
project(F15)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(F15 ${SOURCE_FILES})