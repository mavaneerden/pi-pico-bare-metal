/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

typedef struct
{
    /* Control and Status. */
    union
    {
        struct
        {
            /* Divides the PLL input reference clock.
             * Behaviour is undefined for div=0.
             * PLL output will be unpredictable during refdiv changes,
             * wait for lock=1 before using it.
             * Minimum reference frequency is 5 MHz, so for the Pico it should be 1.
             *
             * Type: RW
             * Reset: 0x01
             */
            uint32_t REFDIV : 6;
            uint32_t : 2;
            /* Passes the reference clock to the output instead of the
             * divided VCO. The VCO continues to run so the user can
             * switch between the reference clock and the divided VCO
             * but the output will glitch when doing so.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t BYPASS : 1;
            uint32_t : 22;
            /* PLL is locked.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t  LOCK : 1;
        };
        /* All register bits. */
        uint32_t all;
    } CS;

    /* Controls the PLL power modes. */
    union
    {
        struct
        {
            /* PLL powerdown. To save power set high when PLL output not required.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t PD : 1;
            uint32_t : 1;
            /* PLL DSM powerdown. Nothing is achieved by setting this low.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t DSMPD : 1;
            /* PLL post divider powerdown
             * To save power set high when PLL output not required or
             * bypass=1.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t POSTDIVPD : 1;
            uint32_t : 1;
            /* PLL VCO powerdown
             * To save power set high when PLL output not required or
             * bypass=1.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t VCOPD : 1;
            uint32_t : 26;
        };
        /* All register bits. */
        uint32_t all;
    } PWR;

    /* Feedback divisor: min=16, max=320. */
    uint32_t FBDIV_INT : 12;

    /* Controls the PLL post dividers for the primary output.
     * The primary output is driven from VCO divided by POSTDIV1 * POSTDIV2.
     */
    union
    {
        struct
        {
            uint32_t : 12;
            /* Divide by 1-7. Undefined for 0.
             * Should be <= POSTDIV1.
             *
             * Type: RW
             * Reset: 0x7
             */
            uint32_t POSTDIV2 : 3;
            uint32_t : 1;
            /* Divide by 1-7. Undefined for 0.
             * Should be >= POSTDIV2.
             *
             * Type: RW
             * Reset: 0x7
             */
            uint32_t POSTDIV1 : 3;
            uint32_t : 13;
        };
        uint32_t all;
    } PRIM;
} PLL_registers_t;


extern volatile PLL_registers_t PLL_SYS;
extern volatile PLL_registers_t PLL_SYS_XOR;
extern volatile PLL_registers_t PLL_SYS_SET;
extern volatile PLL_registers_t PLL_SYS_CLEAR;

extern volatile PLL_registers_t PLL_USB;
extern volatile PLL_registers_t PLL_USB_XOR;
extern volatile PLL_registers_t PLL_USB_SET;
extern volatile PLL_registers_t PLL_USB_CLEAR;
