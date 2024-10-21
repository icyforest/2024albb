cmake_minimum_required(VERSION 3.29)
project(ga)

set(CMAKE_CXX_STANDARD 20)

add_executable(ga main.cpp maze.cpp ga.cpp)
