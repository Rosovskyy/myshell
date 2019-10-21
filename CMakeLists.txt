cmake_minimum_required(VERSION 3.12)
project(myshell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_filesystem")
set(CMAKE_CXX_STANDARD 14)

add_executable(myshell sources/main.cpp sources/helpers.cpp headers/helpers.h)