project (ZipImage)

cmake_minimum_required(VERSION 2.6)

file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

ImagineAddExecutable(test_zipimage example.cpp ../quadtree/quadtree.h)
# ImagineAddExecutable(zipimage main.cpp ../quadtree/quadtree.h)

ImagineUseModules(test_zipimage Graphics)
# ImagineUseModules(zipimage Graphics)
