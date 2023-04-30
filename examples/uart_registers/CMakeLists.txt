##### BUILD EXAMPLE #####
add_executable(uart_registers main.cpp) # Add target executable.
set_target_properties(uart_registers PROPERTIES OUTPUT_NAME main.elf)
target_include_directories(uart_registers PUBLIC ${LIB_INCLUDE_DIR}) # Look here for include files.
target_link_libraries(uart_registers pi-pico-bare-metal) # Link bare metal library to target.
target_compile_features(uart_registers PUBLIC cxx_std_20) # Set minimum standard library to C++20.
