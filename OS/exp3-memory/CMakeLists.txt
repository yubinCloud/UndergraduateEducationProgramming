cmake_minimum_required(VERSION 3.17)
project(exp3_memory)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp3_memory main.cpp PartitionItem.cpp PartitionItem.h MemoryManager.cpp MemoryManager.h FreePartitionList.cpp FreePartitionList.h)