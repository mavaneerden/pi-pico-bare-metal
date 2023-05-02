
set(TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin/ CACHE PATH "Path to 'bin' folder for ARM toolchain.")


set(CMAKE_SYSTEM_NAME               Generic) # OS name. No OS assumed, so Generic is used.
# set(CMAKE_SYSTEM_VERSION            0) # Must be set when specifying system name.
set(CMAKE_SYSTEM_PROCESSOR          cortex-m0plus) # Target processor (passed to --mcpu in compiler).

set(CMAKE_AR                        ${TOOLCHAIN_PATH}/arm-none-eabi-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER              ${TOOLCHAIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PATH}/arm-none-eabi-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER                    ${TOOLCHAIN_PATH}/arm-none-eabi-ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB                    ${TOOLCHAIN_PATH}/arm-none-eabi-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE                      ${TOOLCHAIN_PATH}/arm-none-eabi-size${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP                     ${TOOLCHAIN_PATH}/arm-none-eabi-strip${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

# Compiler flags: https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
set(CMAKE_C_FLAGS "--specs=nosys.specs -mthumb -march=armv6-m -Wall -Wextra -Wshadow -Wundef -Wconversion -W -g -ggdb -u interrupt_vector_table -O0 -fstack-usage -ffreestanding -fno-common -ffunction-sections -fdata-sections -nostartfiles -Wl,--gc-sections -Wl,-static -Wl,-Map=main.map -L ${LINKER_DIR} -T ${LINKER_SCRIPT}") # -nostdlib -nostdinc
# Explanation of C++ flags:
# - Add all C flags.
# - Use -fno-exceptions to disable exception generating code. This is already the default for C sources.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions")

set(CMAKE_LINK_FLAG)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
