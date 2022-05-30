cmake_minimum_required(VERSION 3.14)
project(i3000)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS true)

# enforce x86 compilation
set(CMAKE_GENERATOR_PLATFORM x86)

include_directories(include)

add_subdirectory(components)
