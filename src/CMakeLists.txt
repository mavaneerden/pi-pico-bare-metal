##### SPECIFY LIBRARY SOURCES AND HEADERS #####
set(LIB_SOURCES rp2040_startup.cpp rp2040_vector_table.cpp registers/definitions.cpp hardware_abstraction_layer/gpio/gpio.cpp) # Specify library source files.
set(LIB_HEADERS rp2040_vector_table.hpp registers/ssi.hpp registers/xip.hpp registers/pads.hpp hardware_abstraction_layer/gpio/gpio.hpp) # Specify library header files.

##### ADD LIBRARY TARGET #####
add_library(pi-pico-bare-metal ${LIB_SOURCES} ${LIB_HEADERS}) # Add library with specified sources and headers.
target_include_directories(pi-pico-bare-metal PUBLIC ${LIB_INCLUDE_DIR}) # Look here for include files.
set_target_properties(pi-pico-bare-metal PROPERTIES LINKER_LANGUAGE CXX) # Set linker language for library to C++.
target_compile_features(pi-pico-bare-metal PUBLIC cxx_std_20) # Set minimum standard library to C++20.
