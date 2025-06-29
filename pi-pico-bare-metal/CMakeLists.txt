cmake_minimum_required(VERSION 3.22)

project(pi-pico-bare-metal VERSION 0.1) # Declare project.
enable_language(CXX) # Set project language to C++.

############ VARIABLES ############
set(PICO_LINKER_DIR ${CMAKE_CURRENT_LIST_DIR}/linker)
set(PICO_LINKER_SCRIPT rp2040_linker_script.ld)

set(COMPILE_FLAGS_DEBINFO
    -ggdb3
)

set(COMPILE_FLAGS_DEBUG
    -O0
    -fno-common  # Catches duplicate symbols at link time, has slight performance penalty
)

############ ADD LIBRARY TARGET ############
# Add library with specified sources.
add_library(${PROJECT_NAME} STATIC)

# Add source files here
target_sources(${PROJECT_NAME}
    PUBLIC

    PRIVATE
        src/rp2040/rp2040_startup.cpp
        src/rp2040/rp2040_vector_table.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER
    # Put public headers here
)

# Look here for include files.
target_include_directories(${PROJECT_NAME} PRIVATE
    src
)

# Set linker language for library to C++.
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Set minimum standard library to C++23.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Set compiler options
# target_compile_options(${PROJECT_NAME} PRIVATE
#     "$<BUILD_INTERFACE:-fstack-usage;-ffreestanding;-ffunction-sections;-fdata-sections;-fno-exceptions;-Wall;-Wextra;-Wpedantic;-Wshadow;-Wformat=2;-Wformat-truncation=2;-Wformat-overflow=2;-Wconversion;$<$<CONFIG:Debug>:${COMPILE_FLAGS_DEBUG}>;$<$<CONFIG:Debug,RelWithDebInfo>:${COMPILE_FLAGS_DEBINFO}>;>"
# )
target_compile_options(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:
        -nostartfiles                   # Do not use the "normal" startup files
        --specs=nano.specs              # Disable system calls, they must be implemented manually
        -fstack-usage                   # Creates file that states max stack usage per function
        -ffreestanding                  # Directs compiler to assume standard functions don't have their normal definition (e.g. printf)
        -ffunction-sections             # Make every function have its own section, allows the linker to remove that section if the function is not used together with --gc-sections in the linker
        -fdata-sections                 # Same as -ffunction-sections, but with variables instead of functions
        -fno-exceptions                 # No exceptions in code
        # WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wformat-truncation
        -Wformat-overflow
        -Wconversion
        $<$<CONFIG:Debug>:${COMPILE_FLAGS_DEBUG}>
        $<$<CONFIG:Debug,RelWithDebInfo>:${COMPILE_FLAGS_DEBINFO}>
        -Wl,--gc-sections                   # Remove unused linker sections
        -Wl,-static                         # Does not depend on dynamic run-time libraries
        -L ${PICO_LINKER_DIR}
        -T ${PICO_LINKER_SCRIPT}
    >
)

# Set linker options
target_link_options(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:
    >
)

############ INSTALLATION ############
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pico
)
