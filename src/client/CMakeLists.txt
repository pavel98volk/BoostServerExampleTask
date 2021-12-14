cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CLIENT_SRC src/*.cpp)
file(GLOB_RECURSE CLIENT_H include/*.h)

add_executable(client main.cpp ${CLIENT_SRC} ${CLIENT_H})
target_include_directories(client PUBLIC include)

target_link_libraries(client ${CONAN_LIBS} utils)