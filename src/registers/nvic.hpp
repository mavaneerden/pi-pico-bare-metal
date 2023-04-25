/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

enum irq_numbers
{
    IRQ_NUMBER_TIMER_IRQ_0 = 0u,
    IRQ_NUMBER_TIMER_IRQ_1 = 1u,
    IRQ_NUMBER_TIMER_IRQ_2 = 2u,
    IRQ_NUMBER_TIMER_IRQ_3 = 3u,
    IRQ_NUMBER_PWM_IRQ_WRAP = 4u,
    IRQ_NUMBER_USBCTRL_IRQ = 5u,
    IRQ_NUMBER_XIP_IRQ = 6u,
    IRQ_NUMBER_PIO0_IRQ_0 = 7u,
    IRQ_NUMBER_PIO0_IRQ_1 = 8u,
    IRQ_NUMBER_PIO1_IRQ_0 = 9u,
    IRQ_NUMBER_PIO1_IRQ_1 = 10u,
    IRQ_NUMBER_DMA_IRQ_0 = 11u,
    IRQ_NUMBER_DMA_IRQ_1 = 12u,
    IRQ_NUMBER_IO_IRQ_BANK0 = 13u,
    IRQ_NUMBER_IO_IRQ_QSPI = 14u,
    IRQ_NUMBER_SIO_IRQ_PROC0 = 15u,
    IRQ_NUMBER_SIO_IRQ_PROC1 = 16u,
    IRQ_NUMBER_CLOCKS_IRQ = 17u,
    IRQ_NUMBER_SPI0_IRQ = 18u,
    IRQ_NUMBER_SPI1_IRQ = 19u,
    IRQ_NUMBER_UART0_IRQ = 20u,
    IRQ_NUMBER_UART1_IRQ = 21u,
    IRQ_NUMBER_ADC_IRQ_FIFO = 22u,
    IRQ_NUMBER_I2C0_IRQ = 23u,
    IRQ_NUMBER_I2C1_IRQ = 24u,
    IRQ_NUMBER_RTC_IRQ = 25u,
    IRQ_NUMBER_IRQ_26 = 26u,
    IRQ_NUMBER_IRQ_27 = 27u,
    IRQ_NUMBER_IRQ_28 = 28u,
    IRQ_NUMBER_IRQ_29 = 29u,
    IRQ_NUMBER_IRQ_30 = 30u,
    IRQ_NUMBER_IRQ_31 = 31u
};

typedef struct
{
    uint32_t ISER;
    uint32_t __reserved0[31];

    uint32_t ICER;
    uint32_t __reserved1[31];

    uint32_t ISPR;
    uint32_t __reserved2[31];

    uint32_t ICPR;
    uint32_t __reserved3[95];

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_0 : 2;
            uint32_t : 6;
            uint32_t IP_1 : 2;
            uint32_t : 6;
            uint32_t IP_2 : 2;
            uint32_t : 6;
            uint32_t IP_3 : 2;
        };
        uint32_t all;
    } IPR0;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_4 : 2;
            uint32_t : 6;
            uint32_t IP_5 : 2;
            uint32_t : 6;
            uint32_t IP_6 : 2;
            uint32_t : 6;
            uint32_t IP_7 : 2;
        };
        uint32_t all;
    } IPR1;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_8 : 2;
            uint32_t : 6;
            uint32_t IP_9 : 2;
            uint32_t : 6;
            uint32_t IP_10 : 2;
            uint32_t : 6;
            uint32_t IP_11 : 2;
        };
        uint32_t all;
    } IPR2;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_12 : 2;
            uint32_t : 6;
            uint32_t IP_13 : 2;
            uint32_t : 6;
            uint32_t IP_14 : 2;
            uint32_t : 6;
            uint32_t IP_15 : 2;
        };
        uint32_t all;
    } IPR3;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_16 : 2;
            uint32_t : 6;
            uint32_t IP_17 : 2;
            uint32_t : 6;
            uint32_t IP_18 : 2;
            uint32_t : 6;
            uint32_t IP_19 : 2;
        };
        uint32_t all;
    } IPR4;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_20 : 2;
            uint32_t : 6;
            uint32_t IP_21 : 2;
            uint32_t : 6;
            uint32_t IP_22 : 2;
            uint32_t : 6;
            uint32_t IP_23 : 2;
        };
        uint32_t all;
    } IPR5;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_24 : 2;
            uint32_t : 6;
            uint32_t IP_25 : 2;
            uint32_t : 6;
            uint32_t IP_26 : 2;
            uint32_t : 6;
            uint32_t IP_27 : 2;
        };
        uint32_t all;
    } IPR6;

    union
    {
        struct
        {
            uint32_t : 6;
            uint32_t IP_28 : 2;
            uint32_t : 6;
            uint32_t IP_29 : 2;
            uint32_t : 6;
            uint32_t IP_30 : 2;
            uint32_t : 6;
            uint32_t IP_31 : 2;
        };
        uint32_t all;
    } IPR7;
} NVIC_registers_t;

extern volatile NVIC_registers_t NVIC;
