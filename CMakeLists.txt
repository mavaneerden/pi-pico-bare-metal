# Require minimum version to avoid problems.
cmake_minimum_required(VERSION 3.22.1)

# Set toolchain file to define compiler settings.
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)

project("pi-pico-bare-metal")
enable_language(CXX)
add_executable(main.elf examples/main.cpp)
