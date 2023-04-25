/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#include "rp2040_vector_table.hpp"
#include "registers/ssi.hpp"

/* External symbols provided by linker. */
extern uint32_t __flash_text_start__;
extern uint32_t __flash_data_start__;
extern uint32_t __text_start__;
extern uint32_t __text_end__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

/* Main function called in the Reset handler. */
extern int main(void);

#ifdef __cplusplus
extern "C" { /* Required to avoid name mangling for Reset handler and entry point in linker. */
#endif

/**
 * Called by the second stage boot loader.
 * Calls 'main' after setting up the Pico.
 */
void Reset_handler(void) {
    // TODO: set up clocks and PLLs
    // TODO: some other initialisation?
    // TODO: set up QSPI for better XIP --> put .text in flash --> only put small section in SRAM?

    /* Call main. */
    main();

    // TODO: call some handler here if main returns
}

/**
 * RP2040 second stage boot loader. This function must configure the communication to the Flash chip (W25Q16JVUXIQ)
 * such that its contents can be copied to the processor for execution. After it is configured, the RP2040 will automatically
 * send read command whenever the program reads from flash.
 * This function can be at most 252 bytes long. After that, it needs to give control to a different function.
 *
 * Must be naked, otherwise tries to use the stack pointer (which is not yet initialised).
 *
 * We cannot use individual bitfield addressing for the CTRLR0 and SPI_CTRLR0 registers because that takes up too much memory with -O0.
 */
// TODO: section is too large when using -O3.
__attribute__((naked, section(".flash_second_stage.entry_point"))) void rp2040_startup_flash_second_stage(void)
{
    /* Disable SSI to allow configuration. */
    SSI.SSIENR.SSI_EN = 0u;

    /* Set highest baud rate (i.e. lowest clock divider). Minimum divider is 2, see section 4.10.4 in the RP2040 datasheet. */
    SSI.BAUDR.SCKDV = 2u;

    /* Set the CTRLR0 register. */
    // TODO: use enums here!
    SSI.CTRLR0.all =
        (0x0u                        << 21u) | /* SSI.CTRLR0.SPI_FRF = 0x0u;                        Use 1 bit per clock, see section 9.2.6 in the W25Q16JVUXIQ datasheet. */
        (SSI_CTRLR0_TMOD_EEPROM_READ << 8u)  | /* SSI.CTRLR0.TMOD = SSI_CTRLR0_TMOD_EEPROM_READ;    First transmit instructions, then receive. Required for proper flash operation because we need to send the read command. */
        ((32u - 1u)                  << 16u);  /* SSI.CTRLR0.DFS_32 = 32u - 1u;                     The flash memory outputs 8 bits of data for each instruction, but the address is automatically incremented, allowing for a continuous data stream (see section 9.2.6 in the W25Q16JVUXIQ datasheet).
                                                *                                                   This means we can use the maximum number of bits for each transaction, at 32 bits.
                                                *                                                   We need to fill in 31 as the register value is is n + 1, see section 4.10.13 in the RP2040 datasheet.
                                                */

    /* Set the SPI_CTRLR0 register. */
    // TODO: use enums and flash chip driver here!
    SSI.SPI_CTRLR0.all =
        (0x03u      << 24u) | /* SSI.SPI_CTRLR0.XIP_CMD = 0x03u;     The XIP command we want to use is Read. This is 0x03 for the W25Q16JVUXIQ, see section 9.2.6 in its datasheet. */
        ((24u / 4u) << 2u)  | /* SSI.SPI_CTRLR0.ADDR_L = 24u / 4u;   The W25Q16JVUXIQ uses 24 address bits (see section 9.2.6 in the W25Q16JVUXIQ datasheet), this register has that value divided by 4 (see section 4.10.13 in the RP2040 datasheet). */
        (0x02u      << 8u)  | /* SSI.SPI_CTRLR0.INST_L = 0x2u;       The instruction length is 8 bits, so value 0x02 (see section 4.10.13 in the RP2040 datasheet). */
        (0x0        << 0u);   /* SSI.SPI_CTRLR0.TRANS_TYPE = 0x0u;   Use standard SPI frame format (corresponds to the value in SSI.CTRLR0.SPI_FRF). */

    /* Any data frames sent by the flash chip can be ignored, so we have 0 data frames. */
    SSI.CTRLR1.NDF = 0u;

    /* Enable SSI. */
    SSI.SSIENR.SSI_EN = 1u;

    /* Copy the .text and .data sections from flash to SRAM. */
    // TODO: keep .text in flash and use QSPI.
    uint32_t *flash_source_pointer = &__flash_text_start__;
    uint32_t *sram_destination_pointer = &__text_start__;

    while (sram_destination_pointer < &__data_end__)
    {
        *sram_destination_pointer++ = *flash_source_pointer++;
    }

    /* Initialize the .bss section to 0, as it contains uninitialized data. */
    sram_destination_pointer = &__bss_start__;

    while (sram_destination_pointer < &__bss_end__)
    {
        *sram_destination_pointer++ = 0;
    }

    /* Put the interrupt vector table address into the VTOR register so the processor knows where it is. */
    // TODO: use actual VTOR bitfield.
    (*((volatile unsigned int*)0xe000ed08)) = (uint32_t) interrupt_vector_table;

    /* Set the main stack pointer to the first element in the VTOR table. */
    asm("msr msp, %[stack_top_ptr]" :: [stack_top_ptr] "r" (interrupt_vector_table[0]));

    /* Call the reset handler (2nd element in VTOR table). */
    ((void (*)(void)) interrupt_vector_table[1])();

    /* Signal to the compiler that this code is unreachable: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
    __builtin_unreachable();
}

#ifdef __cplusplus
} /* extern "C" */
#endif
