cmake_minimum_required(VERSION 3.12)
project(image-filter CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

add_subdirectory(plugins)