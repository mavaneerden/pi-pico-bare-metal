/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#include "rp2040_vector_table.hpp"
#include "registers/qspi.hpp"
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

/* Main function called by the startup function. */
extern int main(void);

#ifdef __cplusplus
extern "C" { /* Required to avoid name mangling. */
#endif

#define PUT32(address,value)  (*((volatile unsigned int*)address))=value
#define GET32(address) *(volatile unsigned int*)address

/**
 * RP2040 second stage boot loader.
 * Performs the following functions:
 * - Copy .text section from flash to SRAM.
 * - Copy .data section from flash to SRAM.
 * - Initialize .bss section to 0.
 *
 * Must be naked, otherwise tries to use the stack pointer (which is not yet initialised).
 *
 * This function is very short, as the writes to bit fields are very memory intensive when optimization is not enabled.
 * So we will easily reach the 252 byte limit before we are done setting up.
 */
__attribute__((naked, section(".flash_second_stage.entry_point"))) void rp2040_startup_flash_second_stage(void)
{

    /***** Copy .text section from flash to SRAM. *****/
    // uint32_t section_size = &__text_end__ - &__text_start__;
    // uint32_t *source_ptr = (uint32_t*) &__flash_text_start__;
    // uint32_t *destination_ptr = (uint32_t*) &__text_start__;

    // // TODO: use pico ROM memcpy.
    // for (uint32_t i = 0; i < section_size; i++)
    // {
    //     *destination_ptr++ = *source_ptr++;
    // }

    // /***** Copy .data section from flash to SRAM. *****/
    // section_size = &__data_end__ - &__data_start__;
    // source_ptr = (uint32_t*) &__flash_data_start__;
    // destination_ptr = (uint32_t*) &__data_start__;

    // // TODO: use pico ROM memcpy.
    // for (uint32_t i = 0; i < section_size; i++)
    // {
    //     *destination_ptr++ = *source_ptr++;
    // }

    // /***** Initialise .bss section to 0. *****/
    // section_size = &__bss_end__ - &__bss_start__;
    // // destination_ptr = (uint32_t*) &__bss_start__;

    // // TODO: use pico ROM memset.
    // for (uint32_t i = 0; i < section_size; i++)
    // {
    //     *destination_ptr++ = 0;
    // }

    /* The Pi Pico uses the W25Q16JVUXIQ flash memory chip, so I will use the configuration here: https://github.com/raspberrypi/pico-sdk/blob/2ccab115de0d42d31d6611cca19ef0cd0d2ccaa7/src/rp2_common/boot_stage2/boot2_w25q080.S */
    PADS_QSPI.GPIO_QSPI_SCLK.DRIVE = PADS_QSPI_DRIVE_8mA;
    PADS_QSPI.GPIO_QSPI_SCLK.SLEWFAST = 1;

    /* Disable input Schmitt to reduce delay. */
    PADS_QSPI.GPIO_QSPI_SD0.SCHMITT = 0;
    PADS_QSPI.GPIO_QSPI_SD1.SCHMITT = 0;
    PADS_QSPI.GPIO_QSPI_SD2.SCHMITT = 0;
    PADS_QSPI.GPIO_QSPI_SD3.SCHMITT = 0;

    /* Disable SSI to allow configuration. */
    SSI.SSIENR.SSI_EN = 0;

    /* Set highest baud rate (i.e. lowest clock divider). Minimum divider is 2, see section 4.10.4 in the RP2040 datasheet. */
    SSI.BAUDR.SCKDV = 2;

    /* Use 1 byte offset, for explanation see https://github.com/raspberrypi/pico-sdk/blob/2ccab115de0d42d31d6611cca19ef0cd0d2ccaa7/src/rp2_common/boot_stage2/boot2_w25q080.S. */
    SSI.RX_SAMPLE_DLY.RSD = 1;

    /* 8 bits per data frame. */
    SSI.CTRLR0.DFS_32 = 7;

    /* Enable both transmit and receive mode to allow for two-way communication. */
    SSI.CTRLR0.TMOD = SSI_CTRLR0_TMOD_BOTH_TX_AND_RX;

    /* Enable SSI. */
    SSI.SSIENR.SSI_EN = 1;
}

/**
 * This function programs the status register of the W25Q16JVUXIQ flash chip to use Quad SPI (QSPI).
 * First, check if QSPI is already enabled, if it is we can skip programming the status register.
 * If it isn't enabled yet, enable it.
 */
__attribute__((naked, section(".flash_second_stage.program_status_register"))) void rp2040_startup_program_w25q16jvuxiq_status_register(void)
{
    unsigned int a = 0;
    /* We want to read the Quad Enable (QE) bit from status register 9 (S9), see section 8 of the W25Q16JVUXIQ datasheet.
     * To do this, we need to issue the 'Read Status Register-2' comand (code 0x35), which reads S8 through S16 (see section 9.1.2 of the W25Q16JVUXIQ datasheet).
     */
    // SSI.DR0.DR = 0x35;
    SSI.DR0.DR = 0x9F;

    /* We need to write a dummy byte because the result is only available after 8 clock cycles.
     * This means we need to keep the CS low for an extra 8 clock cycles after that so the result can be read.
     * See section 9.2.4 of the W25Q16JVUXIQ datasheet.
     */
    SSI.DR0.DR = 0x00;

    /* Wait until the TX FIFO is empty. */
    while (!SSI.SR.TFE);

    /* Wait until SSI is not busy. */
    while (SSI.SR.BUSY);

    /* Read the response. Discard the first byte. Not sure why this is done in the Pico SDK, but it may be because
     * the first byte is actually read at the same time that the first byte is transmitted, so it effectively reads garbage.
     * Add volatile here so compiler does not optimize it away.
     */
    // volatile uint8_t byte_read = SSI.DR0.DR;
    // byte_read = SSI.DR0.DR;
    // Should read 0xEF = 239

    /* Since we are reading S9, we want to specifically check bit1. If bit1 is 0, we need to program the status register. */
    // if ((byte_read & 0b00000010) == 0)
    // {
    //     /* code */
    // }


    PUT32( 0x4000f000, ( 1 << 5 ) );               // IO BANK

    while ( (GET32( 0x4000c008 ) & ( 1<< 5 )) == 0 );  // Reset Done?

    PUT32( 0x400140cc, 0x05 );                     // IO PAD = FUNC 5 (GPIO)
    PUT32( 0xd0000020, ( 1 << 25 ) );              // GPIO_OE

    while( 1 )
    {
            PUT32( 0xd000001c, ( 1 << 25 ) );      // XOR GPIO
            for (a = 200000; a > 0; a-- );
    }

}

#ifdef __cplusplus
}
#endif
