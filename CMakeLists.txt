cmake_minimum_required(VERSION 4.1)
project(kvstore)

set(CMAKE_CXX_STANDARD 20)

add_executable(kvstore main.cpp
        kvstore.cpp
        kvstore.h)
