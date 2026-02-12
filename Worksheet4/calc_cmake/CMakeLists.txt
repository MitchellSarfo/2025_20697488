cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(calc)

add_library(maths adder.cpp)

# If building a static library, set a macro so adder.h knows
if (NOT BUILD_SHARED_LIBS)
  add_definitions(-Dmaths_STATIC)
endif()

add_executable(calc calc.cpp)
target_link_libraries(calc maths)
