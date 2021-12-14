cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SERVER_SRC src/*.cpp)
file(GLOB_RECURSE SERVER_H include/*.h)


add_executable(server main.cpp ${SERVER_SRC} ${SERVER_H})
target_include_directories(server PUBLIC include)

target_link_libraries(server ${CONAN_LIBS} utils)