/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

/* Crystal oscillator frequency is 12 MHz. See Appendix B of the Pico datasheet.  */
constexpr uint32_t XOSC_FREQUENCY_HZ = 12000000u;

/* Stabilisation time required for the crystal oscillator is 1 ms. See section 2.16.3 in the RP2040 datasheet. */
constexpr uint32_t XOSC_STABILISATION_TIME_MICROSECONDS = 1000u;

/* Crystal oscillator startup delay, see section 2.16.3 in the RP2040 datasheet.
 * We add 1 to the calculation here to round up the result, so we wait AT LEAST 1 ms.
 */
constexpr uint32_t XOSC_STARTUP_DELAY = (XOSC_FREQUENCY_HZ / XOSC_STABILISATION_TIME_MICROSECONDS) / 256u + 1u;


enum XOSC_CTRL_FREQ_RANGE_value : uint32_t /* Must be uint32_t. Otherwise does not work. */
{
    XOSC_CTRL_FREQ_RANGE_1_15MHZ = 0xAA0u
};

enum XOSC_CTRL_ENABLE_value : uint32_t /* Must be uint32_t. Otherwise does not work. */
{
    XOSC_CTRL_ENABLE = 0xFABu,
    XOSC_CTRL_DISABLE = 0xD1Eu
};

typedef struct
{
    union
    {
        struct
        {
            uint32_t FREQ_RANGE : 12;
            uint32_t ENABLE : 12;
            uint32_t : 8;
        };
        uint32_t all;
    } CTRL;

    union
    {
        struct
        {
            uint32_t FREQ_RANGE : 2;
            uint32_t : 10;
            uint32_t ENABLED : 1;
            uint32_t : 11;
            uint32_t BADWRITE : 1;
            uint32_t : 6;
            uint32_t STABLE : 1;
        };
        uint32_t all;
    } STATUS;

    uint32_t DORMANT;

    union
    {
        struct
        {
            uint32_t DELAY : 14;
            uint32_t : 6;
            uint32_t X4 : 1;
            uint32_t : 11;
        };
        uint32_t all;
    } STARTUP;

    uint32_t __reserved[2];

    uint32_t COUNT : 8;
    uint32_t : 24;
} XOSC_registers_t ;

extern volatile XOSC_registers_t XOSC;
extern volatile XOSC_registers_t XOSC_XOR;
extern volatile XOSC_registers_t XOSC_SET;
extern volatile XOSC_registers_t XOSC_CLEAR;
