cmake_minimum_required(VERSION 3.28)
project(picobaremetal
    VERSION 0.1.0
    DESCRIPTION "Baremetal framework for the Raspberry Pi Pico"
    LANGUAGES CXX)

set(PACKAGE_NAME ${PROJECT_NAME})
set(LIB_TARGET ${PROJECT_NAME})

add_library(${LIB_TARGET} STATIC)

# include(cmake/utils.cmake)
include(GNUInstallDirs)

######### OPTIONS #########
option(PICO_BAREMETAL_BUILD_TESTS "Build ${LIB_TARGET} tests" OFF)
option(PICO_BAREMETAL_BUILD_EXAMPLES "Build ${LIB_TARGET} examples" OFF)
option(PICO_BAREMETAL_INSTALL "Generate target for installing ${LIB_TARGET}"
    ${PROJECT_IS_TOP_LEVEL})
set(PICO_BAREMETAL_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake" CACHE STRING
    "Install path for ${LIB_TARGET} package-related CMake files")


######### HIDE NON-API SYMBOLS #########
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

######### GENERATE EXPORT HEADER #########
include(GenerateExportHeader)
set(export_file_name "export_static.h")
set(export_file_path include/${LIB_TARGET}/${export_file_name})
generate_export_header(${LIB_TARGET} EXPORT_FILE_NAME ${export_file_path})

######### ADD SOURCES #########
if(${PICO_BAREMETAL_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

if(${PICO_BAREMETAL_BUILD_TESTS})
    add_subdirectory(tests)
endif()

add_subdirectory(src)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

list(APPEND PUBLIC_HEADERS
    "${CMAKE_CURRENT_BINARY_DIR}/${export_file_path}")
list(APPEND SOURCES
    "${CMAKE_CURRENT_BINARY_DIR}/${export_file_path}")

######### INITIALISE LIBRARY #########
# Set minimum standard library to C++23.
target_compile_features(${LIB_TARGET} PUBLIC cxx_std_23)

target_sources(${LIB_TARGET} PRIVATE ${SOURCES})

target_include_directories(${LIB_TARGET}
    PUBLIC
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(${LIB_TARGET} PRIVATE
    $<$<CONFIG:Debug>:RP2040_STARTUP_OPT_LEVEL="-Og">
    $<$<AND:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:RP2040_STARTUP_OPT_LEVEL="-Os">
)

set(PICO_BAREMETAL_LINKER_DIR ${CMAKE_CURRENT_LIST_DIR}/linker)
set(PICO_BAREMETAL_LINKER_SCRIPT rp2040_linker_script.ld)
set(COMPILE_FLAGS_DEBINFO
    -ggdb3       # Max debug info for gdb
)
set(COMPILE_FLAGS_DEBUG
    -Og          # -O0 does not inline any functions, so we should use -Og
)
target_compile_options(${LIB_TARGET} PRIVATE
    $<BUILD_INTERFACE:
        -nostartfiles                   # Do not use the "normal" startup files
        --specs=nano.specs              # Disable system calls, they must be implemented manually
        -fstack-usage                   # Creates file that states max stack usage per function
        -ffreestanding                  # Directs compiler to assume standard functions don't have their normal definition (e.g. printf)
        -ffunction-sections             # Make every function have its own section, allows the linker to remove that section if the function is not used together with --gc-sections in the linker
        -fdata-sections                 # Same as -ffunction-sections, but with variables instead of functions
        -fno-exceptions                 # No exceptions in code
        -fno-common                     # Catches duplicate symbols at link time
        # WARNINGS (assumes GCC)
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wformat-truncation
        -Wformat-overflow
        -Wconversion
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wunused
        -Woverloaded-virtual
        -Wsign-conversion
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wnull-dereference
        -Wuseless-cast
        -Wdouble-promotion
        $<$<CONFIG:Debug>:${COMPILE_FLAGS_DEBUG}>
        $<$<CONFIG:Debug,RelWithDebInfo>:${COMPILE_FLAGS_DEBINFO}>
        -Wl,--gc-sections                   # Remove unused linker sections
        -Wl,-static                         # Does not depend on dynamic run-time libraries
        -L ${PICO_BAREMETAL_LINKER_DIR}
        -T ${PICO_BAREMETAL_LINKER_SCRIPT}
    >
)

set_target_properties(${LIB_TARGET} PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
    LINKER_LANGUAGE CXX
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)

######### INSTALL LIBRARY #########
include(GNUInstallDirs)

set(CONFIG_FILE PicoBaremetalConfig)

if(PICO_BAREMETAL_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
install(TARGETS ${LIB_TARGET} EXPORT ${CONFIG_FILE}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_TARGET}
)
export(TARGETS
        ${LIB_TARGET}
    NAMESPACE pico-baremetal::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}.cmake"
)
install(EXPORT
        ${CONFIG_FILE}
    DESTINATION ${PICO_BAREMETAL_INSTALL_CMAKEDIR}
    NAMESPACE YourPackage::
)
endif()
