cmake_minimum_required(VERSION 3.14)

# make it look like we have a choice
# set(CMAKE_GENERATOR "Visual Studio 16 2019" CACHE INTERNAL "" FORCE)
# enforce x86 compilation
# set(CMAKE_GENERATOR_PLATFORM WIN32 CACHE INTERNAL "" FORCE)

project(i3000)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS true)

include_directories(include)

add_subdirectory(components)
