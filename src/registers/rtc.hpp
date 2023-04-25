/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

typedef struct
{
    uint16_t CLKDIV_M1;
    uint32_t : 16;

    union
    {
        struct
        {
            uint32_t DAY : 5;
            uint32_t : 3;
            uint32_t MONTH : 4;
            uint32_t YEAR : 12;
            uint32_t : 8;
        };
        uint32_t all;
    } SETUP_0;

    union
    {
        struct
        {
            uint32_t SEC : 6;
            uint32_t : 2;
            uint32_t MIN : 6;
            uint32_t : 2;
            uint32_t HOUR : 5;
            uint32_t : 3;
            uint32_t DOTW : 3;
            uint32_t : 5;
        };
        uint32_t all;
    } SETUP_1;

    union
    {
        struct
        {
            uint32_t RTC_ENABLE : 1;
            uint32_t RTC_ACTIVE : 1;
            uint32_t : 2;
            uint32_t LOAD : 1;
            uint32_t : 3;
            uint32_t FORCE_NOTLEAPYEAR : 1;
            uint32_t : 23;
        };
        uint32_t all;
    } CTRL;

    union
    {
        struct
        {
            uint32_t DAY : 5;
            uint32_t : 3;
            uint32_t MONTH : 4;
            uint32_t YEAR : 12;
            uint32_t DAY_ENA : 1;
            uint32_t MONTH_ENA : 1;
            uint32_t YEAR_ENA : 1;
            uint32_t : 1;
            uint32_t MATCH_ENA : 1;
            uint32_t MATCH_ACTIVE : 1;
            uint32_t : 2;
        };
        uint32_t all;
    } IRQ_SETUP_0;

    union
    {
        struct
        {
            uint32_t SEC : 6;
            uint32_t : 2;
            uint32_t MIN : 6;
            uint32_t : 2;
            uint32_t HOUR : 5;
            uint32_t : 3;
            uint32_t DOTW : 3;
            uint32_t : 1;
            uint32_t SEC_ENA : 1;
            uint32_t MIN_ENA : 1;
            uint32_t HOUR_ENA : 1;
            uint32_t DOTW_ENA : 1;
        };
        uint32_t all;
    } IRQ_SETUP_1;

    union
    {
        struct
        {
            uint32_t DAY : 5;
            uint32_t : 3;
            uint32_t MONTH : 4;
            uint32_t YEAR : 12;
            uint32_t : 8;
        };
        uint32_t all;
    } RTC_1;

    union
    {
        struct
        {
            uint32_t SEC : 6;
            uint32_t : 2;
            uint32_t MIN : 6;
            uint32_t : 2;
            uint32_t HOUR : 5;
            uint32_t : 3;
            uint32_t DOTW : 3;
            uint32_t : 5;
        };
        uint32_t all;
    } RTC_0;

    union
    {
        struct
        {
            uint32_t RTC;
            uint32_t : 31;
        };
        uint32_t all;
    } INTR;

    union
    {
        struct
        {
            uint32_t RTC;
            uint32_t : 31;
        };
        uint32_t all;
    } INTE;

    union
    {
        struct
        {
            uint32_t RTC;
            uint32_t : 31;
        };
        uint32_t all;
    } INTF;

    union
    {
        struct
        {
            uint32_t RTC;
            uint32_t : 31;
        };
        uint32_t all;
    } INTS;
} RTC_registers_t;

extern volatile RTC_registers_t RTC;
extern volatile RTC_registers_t RTC_XOR;
extern volatile RTC_registers_t RTC_SET;
extern volatile RTC_registers_t RTC_CLEAR;

