/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include "rp2040_constants.hpp"

// TODO: documentation

/* PADS_QSPI drive strength. See section 2.19.6.4 in the RP2040 datasheet. */
enum PADS_QSPI_DRIVE_value : uint8_t {
    PADS_QSPI_DRIVE_2mA = 0x0,
    PADS_QSPI_DRIVE_4mA = 0x1,
    PADS_QSPI_DRIVE_8mA = 0x2,
    PADS_QSPI_DRIVE_12mA = 0x3
};

union PADS_CONTROL
{
    struct
    {
        uint8_t SLEWFAST : 1;
        uint8_t SCHMITT : 1;
        uint8_t PDE : 1;
        uint8_t PUE : 1;
        uint8_t DRIVE : 2;
        uint8_t IE : 1;
        uint8_t OD : 1;
        uint32_t : 24;
    };
    uint32_t all;
};

typedef struct
{
    uint32_t VOLTAGE_SELECT : 1;
    uint32_t : 31;

    union PADS_CONTROL GPIO_QSPI_SCLK;

    union PADS_CONTROL GPIO_QSPI_SD[4];

    union PADS_CONTROL GPIO_QSPI_SS;
} PADS_QSPI_registers_t;

extern volatile PADS_QSPI_registers_t PADS_QSPI;

typedef struct
{
    uint32_t VOLTAGE_SELECT : 1;
    uint32_t : 31;

    union PADS_CONTROL GPIO[30];

    union PADS_CONTROL SWCLK;

    union PADS_CONTROL SWD;
} PADS_BANK0_registers_t;

extern volatile PADS_BANK0_registers_t PADS_BANK0;
extern volatile PADS_BANK0_registers_t PADS_BANK0_XOR;
extern volatile PADS_BANK0_registers_t PADS_BANK0_SET;
extern volatile PADS_BANK0_registers_t PADS_BANK0_CLEAR;
