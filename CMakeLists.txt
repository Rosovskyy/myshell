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

add_executable(mycp sources/mycp.cpp)
target_link_libraries(mycp stdc++fs)

add_executable(mygrep sources/mygrep.cpp)

add_executable(mymkdir sources/mymkdir.cpp ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(mymkdir  boost_system boost_filesystem)

add_executable(mymv sources/mymv.cpp)
target_link_libraries(mymv stdc++fs)

add_executable(myrm sources/myrm.cpp ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(myrm  boost_system boost_filesystem)

add_executable(myls sources/myls.cpp headers/config.h sources/sort.cpp headers/sort.h sources/print.cpp headers/print.h)
target_link_libraries(myls  boost_system boost_filesystem stdc++fs)

set_target_properties(mycp mygrep mymkdir mymv myrm myls mycp
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/log"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/log"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)


