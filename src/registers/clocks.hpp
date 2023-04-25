/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

// TODO: add enums for clock sources

typedef struct
{
    struct
    {
        union
        {
            struct
            {
                uint32_t : 5;
                uint32_t AUXSRC : 4;
                uint32_t : 1;
                uint32_t KILL : 1;
                uint32_t ENABLE : 1;
                uint32_t DC50 : 1;
                uint32_t : 3;
                uint32_t PHASE : 2;
                uint32_t : 2;
                uint32_t NUDGE : 1;
                uint32_t : 11;
            };
            uint32_t all;
        } CTRL;

        union
        {
            struct
            {
                uint32_t FRAC : 8;
                uint32_t INT : 24;
            };
            uint32_t all;
        } DIV;

        uint32_t SELECTED;
    } CLK_GPOUT[4];

    struct
    {
        union
        {
            struct
            {
                uint32_t SRC : 2;
                uint32_t : 3;
                uint32_t AUXSRC : 2;
                uint32_t : 25;
            };
            uint32_t all;
        } CTRL;

        union
        {
            struct
            {
                uint32_t : 8;
                uint32_t INT : 2;
                uint32_t : 22;
            };
            uint32_t all;
        } DIV;

        uint32_t SELECTED;
    } CLK_REF;

    struct
    {
        union
        {
            struct
            {
                uint32_t SRC : 1;
                uint32_t : 4;
                uint32_t AUXSRC : 3;
                uint32_t : 24;
            };
            uint32_t all;
        } CTRL;

        union
        {
            struct
            {
                uint32_t FRAC : 8;
                uint32_t INT : 24;
            };
            uint32_t all;
        } DIV;

        uint32_t SELECTED;
    } CLK_SYS;

    struct
    {
        union
        {
            struct
            {
                uint32_t : 5;
                uint32_t AUXSRC : 3;
                uint32_t : 2;
                uint32_t KILL : 1;
                uint32_t ENABLE : 1;
                uint32_t : 20;
            };
            uint32_t all;
        } CTRL;

        uint32_t SELECTED;
    } CLK_PERI;

    struct CLOCK_USB_ADC
    {
        union
        {
            struct
            {
                uint32_t : 5;
                uint32_t AUXSRC : 3;
                uint32_t : 2;
                uint32_t KILL : 1;
                uint32_t ENABLE : 1;
                uint32_t : 4;
                uint32_t PHASE : 2;
                uint32_t : 2;
                uint32_t NUDGE : 1;
                uint32_t : 11;
            };
            uint32_t all;
        } CTRL;

        union
        {
            struct
            {
                uint32_t : 8;
                uint32_t INT : 2;
                uint32_t : 22;
            };
            uint32_t all;
        } DIV;

        uint32_t SELECTED;
    };
    struct CLOCK_USB_ADC CLK_USB;
    struct CLOCK_USB_ADC CLK_ADC;

    struct
    {
        union
        {
            struct
            {
                uint32_t : 5;
                uint32_t AUXSRC : 3;
                uint32_t : 2;
                uint32_t KILL : 1;
                uint32_t ENABLE : 1;
                uint32_t : 4;
                uint32_t PHASE : 2;
                uint32_t : 2;
                uint32_t NUDGE : 1;
                uint32_t : 11;
            };
            uint32_t all;
        } CTRL;

        union
        {
            struct
            {
                uint32_t FRAC : 8;
                uint32_t INT : 24;
            };
            uint32_t all;
        } DIV;

        uint32_t SELECTED;
    } CLK_RTC;

    union
    {
        struct
        {
            uint32_t TIMEOUT : 8;
            uint32_t ENABLE : 1;
            uint32_t : 3;
            uint32_t FRCE : 1;
            uint32_t : 3;
            uint32_t CLEAR : 1;
            uint32_t : 15;
        };
        uint32_t all;
    } CLK_SYS_RESUS_CTRL;

    union
    {
        struct
        {
            uint32_t RESUSSED : 1;
            uint32_t : 31;
        };
        uint32_t all;
    } CLK_SYS_RESUS_STATUS;

    // TODO: add more registers
} CLOCKS_registers_t;

extern volatile CLOCKS_registers_t CLOCKS;
extern volatile CLOCKS_registers_t CLOCKS_XOR;
extern volatile CLOCKS_registers_t CLOCKS_SET;
extern volatile CLOCKS_registers_t CLOCKS_CLEAR;
