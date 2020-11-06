cmake_minimum_required(VERSION 3.15)
project(eightQueen)

set(CMAKE_CXX_STANDARD 14)

add_executable(eightQueen main.cpp Queen.h Queen_implement.cpp Stack.h Stack_implement.cpp)