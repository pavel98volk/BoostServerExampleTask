
cmake_minimum_required(VERSION 3.12)
project(ClientServerTest)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src/utils)
add_subdirectory(src/client)
add_subdirectory(src/server)