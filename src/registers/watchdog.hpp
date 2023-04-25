/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

typedef struct
{
    union
    {
        struct
        {
            uint32_t TIME : 24;
            uint32_t PAUSE_JTAG : 1;
            uint32_t PAUSE_DBG0 : 1;
            uint32_t PAUSE_DBG1 : 1;
            uint32_t : 3;
            uint32_t ENABLE : 1;
            uint32_t TRIGGER : 1;
        };
        uint32_t all;
    } CTRL;

    uint32_t LOAD : 24;
    uint32_t : 8;

    union
    {
        struct
        {
            uint32_t TIMER : 1;
            uint32_t FORCE : 1;
            uint32_t : 30;
        };
        uint32_t all;
    } REASON;

    uint32_t SCRATCH[8];

    union
    {
        struct
        {
            uint32_t CYCLES : 9;
            uint32_t ENABLE : 1;
            uint32_t RUNNING : 1;
            uint32_t COUNT : 9;
        };
        uint32_t all;
    } TICK;

} WATCHDOG_registers_t;

extern volatile WATCHDOG_registers_t WATCHDOG;
extern volatile WATCHDOG_registers_t WATCHDOG_XOR;
extern volatile WATCHDOG_registers_t WATCHDOG_SET;
extern volatile WATCHDOG_registers_t WATCHDOG_CLEAR;
