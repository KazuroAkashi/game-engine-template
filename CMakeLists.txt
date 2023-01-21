cmake_minimum_required(VERSION 3.16.2)

project(engine-template)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE "LEGACY")

set(PLATFORM GLFW)

if(NOT DEFINED ENV{PROD})
    add_compile_definitions(DEBUG)
endif()

add_subdirectory(engine)
add_subdirectory(sandbox)

target_link_libraries(engine-template-sandbox engine)