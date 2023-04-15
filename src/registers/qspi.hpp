/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

// TODO: documentation
// TODO: unions!

#ifdef __cplusplus
extern "C" {
#endif

/* PADS_QSPI drive strength. See section 2.19.6.4 in the RP2040 datasheet. */
enum PADS_QSPI_DRIVE : uint8_t {
    PADS_QSPI_DRIVE_2mA = 0x0,
    PADS_QSPI_DRIVE_4mA = 0x1,
    PADS_QSPI_DRIVE_8mA = 0x2,
    PADS_QSPI_DRIVE_12mA = 0x3
};

struct PADS_QSPI_struct
{
    uint8_t VOLTAGE_SELECT : 1;
    uint32_t : 31;

    struct GPIO_QSPI_SCLK_struct
    {
        uint8_t SLEWFAST : 1;
        uint8_t SCHMITT : 1;
        uint8_t PDE : 1;
        uint8_t PUE : 1;
        uint8_t DRIVE : 2;
        uint8_t IE : 1;
        uint8_t OD : 1;
        uint32_t : 24;
    } GPIO_QSPI_SCLK;

    struct GPIO_QSPI_SDx_struct
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
    struct GPIO_QSPI_SDx_struct GPIO_QSPI_SD0;
    struct GPIO_QSPI_SDx_struct GPIO_QSPI_SD1;
    struct GPIO_QSPI_SDx_struct GPIO_QSPI_SD2;
    struct GPIO_QSPI_SDx_struct GPIO_QSPI_SD3;

    struct GPIO_QSPI_SS_struct
    {
        uint8_t SLEWFAST : 1;
        uint8_t SCHMITT : 1;
        uint8_t PDE : 1;
        uint8_t PUE : 1;
        uint8_t DRIVE : 2;
        uint8_t IE : 1;
        uint8_t OD : 1;
        uint32_t : 24;
    } GPIO_QSPI_SS;
};

volatile struct PADS_QSPI_struct PADS_QSPI __attribute__((section(".registers.pads_qspi")));

#ifdef __cplusplus
} /* extern "C" */
#endif
