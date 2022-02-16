cmake_minimum_required(VERSION 2.8)

project(PressTest)

set(CMAKE_BUILD_TYPE "Debug")

aux_source_directory(../src DIR_SRCS)
add_executable(PressTest ${DIR_SRCS})
target_link_libraries(PressTest pthread)
