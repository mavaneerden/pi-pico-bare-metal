option(TOOLCHAIN_BIN_PATH "Path to the toolchain 'bin' directory" /usr/bin/)

# OS name. Since this is a bare-metal library, no OS is used.
set(CMAKE_SYSTEM_NAME               Generic)
# Target processor (passed to --mcpu in compiler).
set(CMAKE_SYSTEM_PROCESSOR          cortex-m0plus)
# Type of cross compiler.
set(CROSS_COMPILE arm-none-eabi-)

set(CMAKE_AR                        ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER              ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER                ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER                    ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}objcopy${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_RANLIB                    ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}ranlib${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_SIZE                      ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}size${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_STRIP                     ${TOOLCHAIN_BIN_PATH}${CROSS_COMPILE}strip${CMAKE_EXECUTABLE_SUFFIX})

# Make sure CMake compiles a static library when checking if the compiler is valid.
# This ensures the check does not care about any missing startup symbols, etc.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Search for programs in the host environment, not on the target.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers in the target environment, not the host.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=${CMAKE_SYSTEM_PROCESSOR}")   # ARM Cortex M0+
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=soft")                  # Does not have a floating-point unit
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv6-m")                    # See https://developer.arm.com/Processors/Cortex-M0-Plus
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb")                           # Use the newer Thumb instruction set
