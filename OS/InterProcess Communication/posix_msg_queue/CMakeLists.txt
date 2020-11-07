cmake_minimum_required(VERSION 3.16)
project(posix_msg_queue C)

set(CMAKE_C_STANDARD 99)

add_executable(posix_msg_queue mq_send.c mq_recv.c)