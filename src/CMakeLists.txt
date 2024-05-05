project(image-filter CXX)
set(SOURCES main.cpp plugin_manager.cpp image_filter.cpp)
# Enables -rdynamic flag(GCC), exports all symbols in the executable
set(CMAKE_EXECUTABLE_ENABLE_EXPORTS TRUE)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)