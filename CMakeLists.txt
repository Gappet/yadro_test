# CMakeList.txt : CMake project for Sheet, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project ("Sheet")

# Add source to this project's executable.
add_executable (Sheet "Sheet.cpp" "Sheet.h"   "main.cpp" "Cell.h" "Cell.cpp" "Formula.h" "common.h" "common.cpp" "Formula.cpp" "testSheet.h" "CSVReader.h"  "CSVReader.cpp")



# TODO: Add tests and instal///