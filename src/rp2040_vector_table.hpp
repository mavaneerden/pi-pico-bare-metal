#pragma once

#include <stdint.h>

/* Number of IRQs on the RP2040. See RP2040 data sheet, section 2.3.2.
 * The RP2040 supports all 32 possible external interrupts by setting values in the NVIC, but only 26 are actually implemented in the hardware.
 */
constexpr uint8_t RP2040_NUM_INTERRUPTS = 26u;

/* Interrupt vector size for Cortex M0+.
 * See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 */
constexpr uint8_t CORTEX_M0PLUS_DEFAULT_VECTOR_TABLE_SIZE = 15u;

/* Calculated vector table size. Add 1 for the stack pointer, which is the first element. */
constexpr uint8_t RP2040_VECTOR_TABLE_SIZE = 1u + CORTEX_M0PLUS_DEFAULT_VECTOR_TABLE_SIZE + RP2040_NUM_INTERRUPTS;

/* Make vector table visible for startup file. */
extern "C" volatile void* interrupt_vector_table[RP2040_VECTOR_TABLE_SIZE];
