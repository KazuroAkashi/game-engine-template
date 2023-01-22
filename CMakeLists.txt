cmake_minimum_required(VERSION 3.16.2)

project(engine-template)

#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE "LEGACY")

set(COMPILE_OPTIONS -Wall -Wextra -Wpedantic -Werror -std=c++20)

set(PLATFORM GLFW)

if(NOT DEFINED ENV{PROD})
    add_compile_definitions(DEBUG)
endif()

add_subdirectory(engine)
add_subdirectory(sandbox)

target_compile_options(engine PRIVATE ${COMPILE_OPTIONS})
target_compile_options(engine-template-sandbox PRIVATE ${COMPILE_OPTIONS})

target_link_libraries(engine-template-sandbox engine)