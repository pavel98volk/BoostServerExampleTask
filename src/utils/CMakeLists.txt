cmake_minimum_required(VERSION 3.10)


file(GLOB_RECURSE UTILS_SRC src/*.cpp)
file(GLOB_RECURSE UTILS_H include/*.h)

add_library(utils ${UTILS_SRC} ${UTILS_H})
target_include_directories(utils PUBLIC include)
