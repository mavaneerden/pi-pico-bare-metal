/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#include "rp2040_vector_table.hpp"

/* External symbols provided by linker. */
extern uint32_t __flash_text_start__;
extern uint32_t __flash_data_start__;
extern uint32_t __text_start__;
extern uint32_t __text_end__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

/* Main function called by the startup function. */
extern int main(void);

/* Required to avoid name mangling. */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * RP2040 second stage boot loader.
 * Performs the following functions:
 * - Copy .text section from flash to SRAM.
 * - Copy .data section from flash to SRAM.
 * - Initialize .bss section to 0.
 *
 * Must be naked, otherwise tries to use the stack pointer (which is not yet initialised).
 */
__attribute__((naked, section(".flash_second_stage.entry_point"))) void rp2040_flash_second_stage(void)
{
    // TODO: configure XIP

    /***** Copy .text section from flash to SRAM. *****/
    uint32_t section_size = &__text_end__ - &__text_start__;
    uint32_t *source_ptr = (uint32_t*) &__flash_text_start__;
    uint32_t *destination_ptr = (uint32_t*) &__text_start__;

    // TODO: use pico ROM memcpy.
    for (uint32_t i = 0; i < section_size; i++)
    {
        *destination_ptr++ = *source_ptr++;
    }

    /***** Copy .data section from flash to SRAM. *****/
    section_size = &__data_end__ - &__data_start__;
    source_ptr = (uint32_t*) &__flash_data_start__;
    destination_ptr = (uint32_t*) &__data_start__;

    // TODO: use pico ROM memcpy.
    for (uint32_t i = 0; i < section_size; i++)
    {
        *destination_ptr++ = *source_ptr++;
    }

    /***** Initialise .bss section to 0. *****/
    section_size = &__bss_end__ - &__bss_start__;
    destination_ptr = (uint32_t*) &__bss_start__;

    // TODO: use pico ROM memset.
    for (uint32_t i = 0; i < section_size; i++)
    {
        *destination_ptr++ = 0;
    }

    /* Call main. */
    // main();

    /* Unreachable code as main always loops. */
    // __builtin_unreachable();
}

#ifdef __cplusplus
}
#endif
