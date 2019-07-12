cmake_minimum_required(VERSION 2.6)

project (isotoponyms)

add_executable (isotopo isotopo.cpp town.cpp point2d.cpp)

add_definitions(-DsrcPath="${CMAKE_CURRENT_SOURCE_DIR}")
