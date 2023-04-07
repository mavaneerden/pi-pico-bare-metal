cmake_minimum_required(VERSION 3.22.1) # Require minimum version to avoid problems with earlier versions.

##### SPECIFY DIRECTORIES #####
set(LIB_SRC_DIR ${CMAKE_SOURCE_DIR}/src) # Specify library source directory.
set(LIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include) # Specify library include directory.
set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/examples) # Specify library include directory.
set(CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake) # Specify library include directory.

##### SPECIFY TOOLCHAIN FILE #####
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_DIR}/toolchain.cmake) # Set toolchain file to define compiler settings.

##### CREATE PROJECT #####
project(pi-pico-bare-metal-example VERSION 0.1) # Declare project.
enable_language(CXX) # Set project language to C++.

##### ADD LIBRARY SUB DIRECTORY #####
add_subdirectory(${LIB_SRC_DIR})

##### ADD ALL EXAMPLES #####
add_subdirectory(${EXAMPLES_DIR})
