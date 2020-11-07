cmake_minimum_required(VERSION 3.16)
project(fifo_server C)

set(CMAKE_C_STANDARD 99)

add_executable(fifo_server server.c)