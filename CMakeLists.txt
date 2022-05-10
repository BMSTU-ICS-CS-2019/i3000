cmake_minimum_required(VERSION 3.14)
project(i3000)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS true)

include_directories(include)

add_subdirectory(components)
