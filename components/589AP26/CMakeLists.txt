project(${PROJECT_NAME}-589AP26)

file(GLOB_RECURSE ${PROJECT_NAME}_sources sources/*.cpp)
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources})
target_include_directories(${PROJECT_NAME} PRIVATE include)