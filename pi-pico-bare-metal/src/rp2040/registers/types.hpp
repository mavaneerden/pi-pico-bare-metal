#pragma once

#include <cstdint>

namespace rp2040::registers
{

/**
 * @brief Type for register addresses.
 */
using hw_register_address_t = uintptr_t;

/**
 * @brief Type for register values.
 */
using hw_register_value_t = uint32_t;

/**
 * @brief Type for pointers to registers.
 */
using hw_register_ptr_t = hw_register_value_t*;

}  // namespace rp2040::registers
