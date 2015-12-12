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
add_library(Utils utils.cxx)
add_library(HTTPRequest HTTPRequest.cxx)
add_library(Server server.cxx)
add_library(Socket socket.cxx)
add_library(Debug debug.cxx)

set (EXTRA_LIBS ${EXTRA_LIBS} Server Socket Debug HTTPRequest Utils)

add_executable (HTTPServer main.cxx)
add_executable (Tests tests.cxx)
target_link_libraries (HTTPServer ${EXTRA_LIBS})
target_link_libraries (Tests ${EXTRA_LIBS})

install (TARGETS Utils DESTINATION bin)
install (TARGETS HTTPRequest DESTINATION bin)
install (TARGETS Server DESTINATION bin)
install (TARGETS Socket DESTINATION bin)
install (TARGETS Debug DESTINATION bin)
install (TARGETS HTTPServer DESTINATION bin)

install (FILES utils.h DESTINATION include)
install (FILES HTTPRequest.h DESTINATION include)
install (FILES server.h DESTINATION include)
install (FILES socket.h DESTINATION include)
install (FILES debug.h DESTINATION include)
