cmake_minimum_required(VERSION 3.10.2)
project(test/myshell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lboost_filesystem -lboost_system")
set(CMAKE_CXX_STANDARD 17)
include_directories(headers)

find_package(Boost COMPONENTS system filesystem REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS "-lstdc++fs")

add_executable(myshell sources/main.cpp sources/functions.cpp
        headers/functions.h headers/helpers.h sources/variables.cpp
        headers/variables.h sources/redir.cpp headers/redir.h
        sources/pipeline.cpp headers/pipeline.h
        headers/wildcards.h sources/wildcards.cpp
        ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(myshell boost_system boost_filesystem readline stdc++fs)

