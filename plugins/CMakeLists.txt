project(plugins)

set(SOURCES "plugin1.cpp;plugin2.cpp;plugin3.cpp")
foreach(SRC ${SOURCES})
    get_filename_component(LIB_NAME ${SRC} NAME_WE)
    add_library(${LIB_NAME} SHARED ${SRC})
    target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach(SRC ${SOURCE_FILES})
