cmake_minimum_required(VERSION 3.9)
project(modeling)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/Tree.cpp
        ${CMAKE_SOURCE_DIR}/src/Graph.cpp
        ${CMAKE_SOURCE_DIR}/src/Selection.cpp
        ${CMAKE_SOURCE_DIR}/src/Chain.cpp)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/src/headers/Tree.h
        ${CMAKE_SOURCE_DIR}/src/headers/Graph.h
        ${CMAKE_SOURCE_DIR}/src/headers/Selection.h
        ${CMAKE_SOURCE_DIR}/src/headers/Chain.h)

add_executable(simulation main.cpp ${SOURCES} ${HEADERS})