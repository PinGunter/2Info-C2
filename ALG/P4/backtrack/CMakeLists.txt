cmake_minimum_required(VERSION 3.19)
project(backtrack)

set(CMAKE_CXX_STANDARD 14)

add_executable(backtrack main.cpp Player.cpp Player.h solucion.cpp solucion.h)