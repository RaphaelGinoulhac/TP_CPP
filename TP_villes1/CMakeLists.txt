cmake_minimum_required(VERSION 2.6)

project (villes_les_plus_proches)

add_executable (villes town.cpp example.cpp
 	        point2d.cpp square.cpp quadrant.cpp)
# rm square.cpp quadrant.cpp

#add_executable (test_villes example.cpp town.cpp)

add_definitions(-DsrcPath="${CMAKE_CURRENT_SOURCE_DIR}")
