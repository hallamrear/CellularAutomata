# CMakeList.txt : CMake project for Simulation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_SOURCE_DIR}/HalTec/includes /inc)
link_directories(${CMAKE_SOURCE_DIR}/HalTec/lib /lib)

# Add source to this project's executable.
add_executable (Simulation "GameOfLife.cpp" "GameOfLife.h"  "entry.cpp" "Cell.h" "Cell.cpp" "LangtonsAnt.h" "LangtonsAnt.cpp")

target_link_libraries(Simulation HalTec)

# TODO: Add tests and install targets if needed.
