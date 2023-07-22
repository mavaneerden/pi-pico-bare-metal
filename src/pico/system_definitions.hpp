#pragma once

#include <stdint.h>

namespace pico
{
    /* Crystal oscillator frequency is 12 MHz. See Appendix B of the Pico datasheet.  */
    constexpr uint32_t XOSC_FREQUENCY_HZ = 12000000u;

    /* Stabilisation time required for the crystal oscillator is 1 ms. See section 2.16.3 in the RP2040 datasheet. */
    constexpr uint32_t XOSC_STABILISATION_TIME_MICROSECONDS = 1000u;

    /* Crystal oscillator startup delay, see section 2.16.3 in the RP2040 datasheet.
    * We add 1 to the calculation here to round up the result, so we wait AT LEAST 1 ms.
    */
    constexpr uint32_t XOSC_STARTUP_DELAY = (XOSC_FREQUENCY_HZ / XOSC_STABILISATION_TIME_MICROSECONDS) / 256u + 1u;
} // namespace pico


