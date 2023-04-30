##### BUILD EXAMPLE #####
add_executable(blink_gpio_hal_timer main.cpp) # Add target executable.
set_target_properties(blink_gpio_hal_timer PROPERTIES OUTPUT_NAME main.elf)
target_include_directories(blink_gpio_hal_timer PUBLIC ${LIB_INCLUDE_DIR}) # Look here for include files.
target_link_libraries(blink_gpio_hal_timer pi-pico-bare-metal) # Link bare metal library to target.
target_compile_features(blink_gpio_hal_timer PUBLIC cxx_std_20) # Set minimum standard library to C++20.
