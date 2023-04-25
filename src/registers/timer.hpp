/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

enum TIMER_ALARM_value
{
    TIMER_ALARM_0 = 0u,
    TIMER_ALARM_1 = 1u,
    TIMER_ALARM_2 = 2u,
    TIMER_ALARM_3 = 3u,
};

typedef struct
{
    uint32_t TIMEHW;
    uint32_t TIMELW;
    uint32_t TIMEHR;
    uint32_t TIMELR;

    uint32_t ALARM0;
    uint32_t ALARM1;
    uint32_t ALARM2;
    uint32_t ALARM3;

    uint32_t ARMED : 4;
    uint32_t : 28;

    uint32_t TIMERAWH;
    uint32_t TIMERAWL;

    union
    {
        struct
        {
            uint32_t : 1;
            uint32_t DBG0 : 1;
            uint32_t DBG1 : 1;
            uint32_t : 29;
        };
        uint32_t all;
    } DBGPAUSE;

    uint32_t PAUSE : 1;
    uint32_t : 31;

    union
    {
        struct
        {
            uint32_t ALARM_0 : 1;
            uint32_t ALARM_1 : 1;
            uint32_t ALARM_2 : 1;
            uint32_t ALARM_3 : 1;
            uint32_t : 28;
        };
        uint32_t all;
    } INTR;

    union
    {
        struct
        {
            uint32_t ALARM_0 : 1;
            uint32_t ALARM_1 : 1;
            uint32_t ALARM_2 : 1;
            uint32_t ALARM_3 : 1;
            uint32_t : 28;
        };
        uint32_t all;
    } INTE;

    union
    {
        struct
        {
            uint32_t ALARM_0 : 1;
            uint32_t ALARM_1 : 1;
            uint32_t ALARM_2 : 1;
            uint32_t ALARM_3 : 1;
            uint32_t : 28;
        };
        uint32_t all;
    } INTF;

    union
    {
        struct
        {
            uint32_t ALARM_0 : 1;
            uint32_t ALARM_1 : 1;
            uint32_t ALARM_2 : 1;
            uint32_t ALARM_3 : 1;
            uint32_t : 28;
        };
        uint32_t all;
    } INTS;
} TIMER_registers_t;

extern volatile TIMER_registers_t TIMER;
extern volatile TIMER_registers_t TIMER_XOR;
extern volatile TIMER_registers_t TIMER_SET;
extern volatile TIMER_registers_t TIMER_CLEAR;
