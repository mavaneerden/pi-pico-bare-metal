#pragma once

#include <stdint.h>
// #include "CMSIS/rp2040_cmsis.h"

namespace pico::xosc
{
    /* Crystal oscillator frequency is 12 MHz. See Appendix B of the Pico datasheet.  */
    constexpr uint32_t FREQUENCY_HZ = 12000000u;

    /* Stabilisation time required for the crystal oscillator is 1 ms. See section 2.16.3 in the RP2040 datasheet. */
    constexpr uint32_t STABILISATION_TIME_MICROSECONDS = 1000u;

    /* Crystal oscillator startup delay, see section 2.16.3 in the RP2040 datasheet.
    * We add 1 to the calculation here to round up the result, so we wait AT LEAST 1 ms.
    */
    constexpr uint32_t STARTUP_DELAY = (FREQUENCY_HZ / STABILISATION_TIME_MICROSECONDS) / 256u + 1u;
} // namespace pico

namespace pico::xip::flash
{
    // constexpr XIP_SSI_CTRLR0_SPI_FRF_Enum SPI_FRAME_FORMAT = XIP_SSI_CTRLR0_SPI_FRF_STD;
    // constexpr XIP_SSI_SPI_CTRLR0_TRANS_TYPE_Enum SPI_TRANSFER_TYPE = XIP_SSI_SPI_CTRLR0_TRANS_TYPE_1C1A;
    // constexpr XIP_SSI_SPI_CTRLR0_INST_L_Enum INSTRUCTION_SIZE_BITS = XIP_SSI_SPI_CTRLR0_INST_L_8B;
    constexpr uint8_t DATA_FRAME_SIZE_32_BIT = 32u;
    constexpr uint8_t COMMAND_READ = 0x03u;
    constexpr uint8_t ADDRESS_BITS = 24u;
} // namespace pico::xip::flash


