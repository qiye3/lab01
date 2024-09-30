cmake_minimum_required(VERSION 3.10)
project(lab01)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/Utils)
add_subdirectory(src/Task)
add_subdirectory(src/Task_Manager)

file(GLOB_RECURSE SRC_FILES "src/**/*.cpp")

add_executable(main main.cpp ${SRC_FILES})
target_link_libraries(main Utils Task Task_Manager)