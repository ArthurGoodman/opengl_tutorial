cmake_minimum_required(VERSION 3.0.0)
project(opengl_tutorial)

################################################################################
# CMake options
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

################################################################################
# Compiler settings
################################################################################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wunused-variable
    -Wno-comment
    -Wconversion
    -fdiagnostics-color=always
    )

################################################################################
# Libraries
################################################################################

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# SDL2
find_package(SDL2 REQUIRED)

# glm
find_package(glm REQUIRED)

################################################################################
# Targets
################################################################################

add_subdirectory(src)
add_subdirectory(third_party)
