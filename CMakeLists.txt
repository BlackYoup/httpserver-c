cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project (HTTPServer)

set (HTTPServer_VERSION_MAJOR 0)
set (HTTPServer_VERSION_MINOR 0)
set (HTTPServer_VERSION_PATCH 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

## Libraries
add_library(Server server.cxx)
add_library(Socket socket.cxx)
add_library(Debug debug.cxx)

set (EXTRA_LIBS ${EXTRA_LIBS} Server Socket Debug)

add_executable (HTTPServer main.cxx)
target_link_libraries (HTTPServer ${EXTRA_LIBS})

install (TARGETS Server DESTINATION bin)
install (TARGETS Socket DESTINATION bin)
install (TARGETS Debug DESTINATION bin)
install (TARGETS HTTPServer DESTINATION bin)

install (FILES server.h DESTINATION include)
install (FILES socket.h DESTINATION include)
install (FILES debug.h DESTINATION include)
