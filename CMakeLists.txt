cmake_minimum_required(VERSION 3.9)
project(Computer-simulation)

set(CMAKE_CXX_STANDARD 11)
set(SIMULATION_INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
include_directories(${SIMULATION_INCLUDE_DIR})

add_executable(simulation main.cpp)

target_link_libraries(simulation src)
ADD_DEPENDENCIES(simulation src)