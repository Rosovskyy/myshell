cmake_minimum_required(VERSION 3.10)
project(myshell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lboost_filesystem -lboost_system")
set(CMAKE_CXX_STANDARD 17)
include_directories(headers)

find_package(Boost COMPONENTS system filesystem REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS "-lstdc++fs")

add_executable(myshell sources/main.cpp sources/functions.cpp headers/functions.h headers/helpers.h sources/variables.cpp headers/variables.h sources/wildcards.cpp headers/wildcards.h ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(myshell boost_system boost_filesystem readline stdc++fs)
#target_link_libraries(myshell PRIVATE stdc++fs)

