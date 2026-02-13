cmake_minimum_required(VERSION 3.16)
project(Worksheet5 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(maths src/maths.cpp)
target_include_directories(maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(calc src/calc.cpp)
target_link_libraries(calc PRIVATE maths)

# ---- Doxygen target (Docs via CMake) ----
find_program(DOXYGEN_EXECUTABLE doxygen)
if(DOXYGEN_EXECUTABLE)
  add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation..."
  )
else()
  message(WARNING "Doxygen not found - docs target will not be available")
endif()
# ---- Install rules ----
install(TARGETS calc RUNTIME DESTINATION bin)
install(TARGETS maths
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(FILES include/maths.h DESTINATION include)

# ---- CPack / Installer ----
if(WIN32)
  set(CPACK_GENERATOR "NSIS")
else()
  set(CPACK_GENERATOR "ZIP")
endif()

set(CPACK_PACKAGE_NAME "Worksheet5Calc")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)
