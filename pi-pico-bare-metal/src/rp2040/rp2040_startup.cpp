/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#include <utility>

#include "pico/system_definitions.hpp"
#include "rp2040/registers/list/xip_ctrl.hpp"
#include "rp2040/registers/types.hpp"
// #include "rp2040_registers.hpp"
#include "rp2040_vector_table.hpp"

/* External symbols provided by linker. */
extern const uint32_t ld_flash_text_start;
extern const uint32_t ld_flash_data_start;
extern const uint32_t ld_text_start;
extern const uint32_t ld_text_end;
extern const uint32_t ld_data_start;
extern const uint32_t ld_data_end;
extern const uint32_t ld_bss_start;
extern const uint32_t ld_bss_end;

/* Import constructor array start and end as functions, since they need to be called as functions later. */
extern void (*ld_init_array_start)(); /* Start of the init_array section. */
extern void (*ld_init_array_end)();   /* End of the init_array section. */

/* Main function called in the Reset handler. */
extern auto main() -> int;

/* Settings for XIP flash. */
constexpr uint32_t XIP_SSI_CTRLR0_settings = 0u;
// (pico::xip::flash::SPI_FRAME_FORMAT              << XIP_SSI_CTRLR0_SPI_FRF_Pos) | /* Use 1 bit per clock, see
// section 9.2.6 in the W25Q16JVUXIQ datasheet. */ (XIP_SSI_CTRLR0_TMOD_EEPROM_READ                 <<
// XIP_SSI_CTRLR0_TMOD_Pos)    | /* First transmit instructions, then receive. Required for proper flash operation
// because we need to send the read command. */
// ((pico::xip::flash::DATA_FRAME_SIZE_32_BIT - 1u) << XIP_SSI_CTRLR0_DFS_32_Pos);   /* The flash memory outputs 8 bits
// of data for each instruction, but the address is automatically incremented, allowing for a continuous data stream
// (see section 9.2.6 in the W25Q16JVUXIQ datasheet).
//                                                                                    * This means we can use the
//                                                                                    maximum number of bits for each
//                                                                                    transaction, at 32 bits.
//                                                                                    * We need to fill in 31 as the
//                                                                                    register value is is n + 1, see
//                                                                                    section 4.10.13 in the RP2040
//                                                                                    datasheet.
//                                                                                    */
constexpr uint32_t XIP_SSI_SPI_CTRLR0_settings = 0u;
// (pico::xip::flash::COMMAND_RvEAD          << XIP_SSI_SPI_CTRLR0_XIP_CMD_Pos) |   /* The XIP command we want to use is
// Read. This is 0x03 for the W25Q16JVUXIQ, see section 9.2.6 in its datasheet. */
// ((pico::xip::flash::ADDRESS_BITS / 4u)   << XIP_SSI_SPI_CTRLR0_ADDR_L_Pos)  |   /* The W25Q16JVUXIQ uses 24 address
// bits (see section 9.2.6 in the W25Q16JVUXIQ datasheet), this register has that value divided by 4 (see
// section 4.10.13 in the RP2040 datasheet). */ (pico::xip::flash::INSTRUCTION_SIZE_BITS <<
// XIP_SSI_SPI_CTRLR0_INST_L_Pos)  |   /* The instruction length is 8 bits, so value 0x02 (see section 4.10.13 in the
// RP2040 datasheet). */ (pico::xip::flash::SPI_TRANSFER_TYPE     << XIP_SSI_SPI_CTRLR0_TRANS_TYPE_Pos); /* Use standard
// SPI frame format (corresponds to the value in SSI.CTRLR0.SPI_FRF). */

extern "C" /* Required to avoid name mangling for Reset handler and entry point in linker. */
{
/**
 * Called by the second stage boot loader.
 * Calls 'main' after setting up the Pico.
 */
void Reset_handler(void)
{
    using namespace rp2040::registers;
    // TODO: set up clocks and PLLs
    // TODO: some other initialisation?
    // TODO: set up QSPI for better XIP --> put .text in flash --> only put small section in SRAM?
    xip::ctrl::clear_field<xip::ctrl::err_badwrite>();
    xip::ctrl::set_field<xip::test>(true);
    auto b = xip::ctrl::get_field<xip::ctrl::en>();
    xip::ctrl::set_field<xip::ctrl::power_down>(b);
    xip::ctrl::set_fields<xip::ctrl::power_down, xip::ctrl::err_badwrite>(b, b);
    xip::ctrl::set(0);

    /* Loop over addresses of constructors and call each one. Copied from the Pico SDK.
     * Constructors are called as late as possible to provide the widest constructor functionality.
     */
    for (void (**p)(void) = &ld_init_array_start; p < &ld_init_array_end; ++p)
    {
        (*p)();
    }

    /* Call main. */
    main();

    /* Infinite loop in case main returns. */
    while (1u)
        ;
}

/**
 * RP2040 second stage boot loader. This function must configure the communication to the Flash chip (W25Q16JVUXIQ)
 * such that its contents can be copied to the processor for execution. After it is configured, the RP2040 will
 * automatically send read command whenever the program reads from flash. This function can be at most 252 bytes long.
 * After that, it needs to give control to a different function.
 *
 * Must be naked, otherwise tries to use the stack pointer (which is not yet initialised).
 * Has its own optimisation level, as other optimisation levels could cause the code to go beyond the 252 byte limit.
 */
__attribute__((naked, optimize("Os"), section(".flash_second_stage.entry_point"))) void
rp2040_startup_flash_second_stage(void)
{
    /* Disable SSI to allow configuration. */
    // XIP_SSI->SSIENR = 0u;

    // /* Set highest baud rate (i.e. lowest clock divider). Minimum divider is 2, see section 4.10.4 in the RP2040
    // datasheet. */ XIP_SSI->BAUDR = 2u;

    // /* Set the CTRLR0 register. */
    // XIP_SSI->CTRLR0 = XIP_SSI_CTRLR0_settings;

    // /* Set the SPI_CTRLR0 register. */
    // XIP_SSI->SPI_CTRLR0 = XIP_SSI_SPI_CTRLR0_settings;

    // /* Any data frames sent by the flash chip can be ignored, so we have 0 data frames. */
    // XIP_SSI->CTRLR1 = 0u;

    // /* Enable SSI. */
    // XIP_SSI->SSIENR = 1u;

    /* Copy the .text and .data sections from flash to SRAM. */
    // TODO: keep .text in flash and use QSPI.
    // TODO: move this out of the bootloader
    // TODO: use memcpy
    // uint32_t* flash_source_pointer     = &ld_flash_text_start;
    // uint32_t* sram_destination_pointer = &ld_text_start;

    // while (sram_destination_pointer < &data_end)
    // {
    //     *sram_destination_pointer++ = *flash_source_pointer++;
    // }

    // /* Initialize the .bss section to 0, as it contains uninitialized data. */
    // TODO: move this out of the bootloaer
    // TODO: use memset
    // sram_destination_pointer = &ld_bss_start;

    // while (sram_destination_pointer < &ls_bss_end)
    // {
    //     *sram_destination_pointer++ = 0;
    // }

    /* Put the interrupt vector table address into the VTOR register so the processor knows where it is. */
    // PPB->VTOR = (uintptr_t) interrupt_vector_table;

    /* Set the main stack pointer to the first element in the VTOR table. */
    // asm("msr msp, %[stack_top_ptr]" :: [stack_top_ptr] "r" (interrupt_vector_table[0]));

    /* Call the reset handler (2nd element in VTOR table). */
    CALL_RESET_HANDLER;

    /* Signal to the compiler that this code is unreachable: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
    std::unreachable();
}

} /* extern "C" */
