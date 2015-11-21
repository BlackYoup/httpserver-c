cmake_minimum_required (VERSION 2.6)
project (HTTPServer)

set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 0)
set (Tutorial_VERSION_PATCH 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_BINARY_DIR}")

add_executable (HTTPServer main.cxx)

install (TARGETS HTTPServer DESTINATION bin2)
