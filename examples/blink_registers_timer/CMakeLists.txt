##### BUILD EXAMPLE #####
add_executable(main.elf main.cpp) # Add target executable.
target_include_directories(main.elf PUBLIC ${LIB_INCLUDE_DIR}) # Look here for include files.
target_link_libraries(main.elf pi-pico-bare-metal) # Link bare metal library to target.
target_compile_features(main.elf PUBLIC cxx_std_20) # Set minimum standard library to C++20.
