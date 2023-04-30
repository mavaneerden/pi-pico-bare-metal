/**
 * Author:
 *   Marco van Eerden
 *
 * Description:
 *   Uses the blink example as as base.
 *   Writes messages to UART0 with a baud rate of 9600.
 */

#include "registers.hpp"

/* LED is on GPIO25. */
constexpr uint32_t LED_PIN = 25u;

/* Loop iteration duration. */
constexpr uint32_t ITERATION_DURATION_MICROSECONDS = 500u * 1000u; /* 0.5s */

/* PLL FBDIV value. Must be >= 16 and <= 300. */
constexpr uint32_t PLL_FBDIV_VALUE = 20u;

/* PLL POSTDIV1 value. Divides XOSC * PLL_FBDIV_VALUE. */
constexpr uint32_t PLL_POSTDIV1_VALUE = 2u;

/* PLL POSTDIV1 value. Divides XOSC * FBDIV / POSTDIV1. */
constexpr uint32_t PLL_POSTDIV2_VALUE = 1u;

/**
 * Set up GPIO for blink.
 */
void gpio_setup(void)
{
    /* Reset the IO_BANK0 peripheral by clearing. Necessary, otherwise it does not work. */
    RESETS_CLEAR.RESET.IO_BANK0 = 1u;

    /* Wait until the IO_BANK0 peripheral has reset. */
    while (!RESETS.RESET_DONE.IO_BANK0);

    /* Set output override to default (no override). Using IO_BANK0_SET here does not work. */
    IO_BANK0.GPIO[LED_PIN].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;

    /* Set function to SIO. */
    IO_BANK0.GPIO[LED_PIN].CTRL.FUNCSEL = IOBANK0_GPIOx_CTRL_FUNCSEL_SIO;

    /* Enable output for GPIO 25. */
    SIO.GPIO_OE_SET = 1u << LED_PIN;
}

/**
 * Set up timer for delay.
 */
void timer_setup(void)
{
    /* Reset timer periphteral. */
    RESETS_CLEAR.RESET.TIMER = 1u;

    /* Wait until the TIMER peripheral has reset. */
    while (!RESETS.RESET_DONE.TIMER);

    /* Enable peripheral interrupt for Alarm 0. */
    TIMER_SET.INTE.ALARM_0 = 1u;

    /* Enable processor IRQ for Alarm 0. */
    NVIC.ISER |= 1u << IRQ_NUMBER_TIMER_IRQ_0;
}

/**
 * Set up peripheral clock @ 120 MHz.
 */
void clk_peri_setup(void)
{
    /* Select system clock as clock source (120 MHz). */
    CLOCKS.CLK_PERI.CTRL.AUXSRC = 0x0u;

    /* Enable peripheral clock. */
    CLOCKS.CLK_PERI.CTRL.ENABLE = 1u;
}

/**
 * Set up the pll_sys clock to target 120 MHz = (12 MHz * 20) / (2 * 1).
 * It is 5 MHz slower than the Pico SDK but saves power by having a VCO frequency of 240 MHz
 * instead of the 1500 MHz that the Pico SDK uses.
 *
 * Not strictly necessary for UART but increases the performance of the system by ~10x (12 MHz to 120 MHz).
 */
void pll_setup(void)
{
    /* Reset PLL peripheral. */
    RESETS_CLEAR.RESET.PLL_SYS = 1u;

    /* Wait until reset complete. */
    while (!RESETS.RESET_DONE.PLL_SYS);

    /* Reference clock divider, should be 1 for the Pico. */
    PLL_SYS.CS.REFDIV = 1u;

    /* Set feedback divider. */
    PLL_SYS.FBDIV_INT = PLL_FBDIV_VALUE;

    /* Power up PLL: enable main PLL power. */
    PLL_SYS_CLEAR.PWR.PD = 1u;

    /* Power up PLL: enable VCO power. */
    PLL_SYS_CLEAR.PWR.VCOPD = 1u;

    /* Wait until PLL is locked. */
    while (!PLL_SYS.CS.LOCK);

    /* Set post divider 1. */
    PLL_SYS.PRIM.POSTDIV1 = PLL_POSTDIV1_VALUE;

    /* Set post divider 2. */
    PLL_SYS.PRIM.POSTDIV2 = PLL_POSTDIV2_VALUE;

    /* Power on post dividers. */
    PLL_SYS_CLEAR.PWR.POSTDIVPD = 1u;
}

/**
 * Set up clocks to make timer work with microsecond time.
 * We could also use the Ring Oscillator (used by default), but it is roughly twice as slow (6.5 MHz vs. 12 MHz).
 */
void clock_setup(void)
{
    /* Set crystal oscillator startup delay. */
    XOSC_SET.STARTUP.DELAY = XOSC_STARTUP_DELAY;

    /* Enable crystal oscillator (disabled on reset). */
    XOSC_SET.CTRL.ENABLE = XOSC_CTRL_ENABLE;

    /* Wait until crystal oscillator is stable (XOSC_STARTUP_DELAY * 256 cycles). */
    while (!XOSC.STATUS.STABLE);

    /* Set refrence clock source (used by timer) to crystal oscillator. */
    CLOCKS_SET.CLK_REF.CTRL.SRC = 0x2u;

    /* Set up PLL clock, target 120 MHz. */
    pll_setup();

    /* Set system clock to PLL clock. Used as PCLK by UART peripheral. */
    CLOCKS_SET.CLK_SYS.CTRL.AUXSRC = 0x0;
    CLOCKS_SET.CLK_SYS.CTRL.SRC = 0x1;

    /* Set up peripheral clock, target 12 MHz. */
    clk_peri_setup();
}

/**
 * Target a baud rate of 9600 baud.
 *
 * Calculations (see Section 4.2.7.1 in the RP2040 datasheet):
 * Divisor: 120 MHz / (16 * 9600) = 781.25
 * Integer part: 781
 * Fractional part: int(0.25 * 64 + 0.5) = 16
 * Actual baud rate: 781 + 16 / 64 = 781.25 --> no error :)
 */
void uart_set_baud_rate(void)
{
    UART0.UARTIBRD.BAUD_DIVINT = 781;
    UART0.UARTFBRD.BAUD_DIVFRAC = 16;
}

void uart_setup(void)
{
    RESETS_CLEAR.RESET.UART0 = 1u;

    while (!RESETS.RESET_DONE.UART0);

    uart_set_baud_rate();

    /* Set word length to 8 bits. */
    UART0.UARTLCR_H.WLEN = 0b11;

    /* Enable FIFOs. */
    UART0.UARTLCR_H.FEN = 1u;

    /* Enable UART. */
    UART0.UARTCR.UARTEN = 1u;
    UART0.UARTCR.TXE = 1u;
    UART0.UARTCR.RXE = 1u;

    /* Configure UART TX pin. */
    IO_BANK0.GPIO[0].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
    IO_BANK0.GPIO[0].CTRL.FUNCSEL = IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_TX;

    /* Configure UART RX pin. */
    IO_BANK0.GPIO[1].CTRL.INOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
    IO_BANK0.GPIO[1].CTRL.FUNCSEL = IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_RX;
}

/**
 * Write a byte by writing to the DATA register.
 * Wait until the TX buffer is not full until writing.
 */
void uart_write_byte(uint8_t byte)
{
    /* Wait while TX buffer is full. */
    while (UART0.UARTFR.TXFF);

    /* Write byte to UART. */
    UART0.UARTDR.DATA = byte;
}

/**
 * Write multiple bytes to UART.
 */
void uart_write_bytes(uint8_t* bytes, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        uart_write_byte(bytes[i]);
    }
}

/**
 * Write a string to UART.
 */
void uart_write_string(char* string)
{
    while (*string != '\0')
    {
        uart_write_byte(*string++);
    }
}

/**
 * Flush the TX buffer by filling the TX FIFO with zeroes.
 */
void uart_flush_tx_buffer()
{
    uint8_t bytes[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    uart_write_bytes(bytes, 32);
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 *
 * From https://stackoverflow.com/a/23840699
 * Assumes signed numbers, so does not work as expected for unsigned numbers.
 */
// TODO: use std::string (eventually)
char* itoa(int value, char* result, int base) {
    // check that the base is valid
    if (base < 2 || base > 36) {
        return nullptr;
    }

    char* ptr = result;
    char* ptr1 = result;
    char tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) {
        *ptr++ = '-';
    }

    *ptr-- = '\0';

    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    return result;
}

int main(void)
{
    /* Set up clocks for running timer. */
    clock_setup();

    /* Set up GPIO for LED blink. */
    gpio_setup();

    /* Set up timer for blink interrupt. */
    timer_setup();

    /* Set up UART. */
    uart_setup();

    /* Flush TX buffer, otherwise the first message is garbage. */
    uart_flush_tx_buffer();

    /* Define ITOA result buffer. */
    char itoa_result[32];

    /* Write start message. */
    uart_write_string("Start!\r\n");

    /* Infinite loop. */
    while(true)
    {
        /* Get current time from timer (unsafe). ALARM only works with the lower timer part.
         * This lower part overflows so overflow of the sum below should have the same behaviour.
         */
        uint32_t time_of_next_iteration = TIMER.TIMELR + ITERATION_DURATION_MICROSECONDS;

        /* Toggle the LED pin. */
        SIO.GPIO_OUT_XOR = 1u << LED_PIN;

        /* Configure Alarm 0 to fire at next iteration. */
        TIMER.ALARM0 = time_of_next_iteration;

        /* Sleep until interrupt occurs, see section A6.7.76 in the ARMv6-M architecture reference manual. */
        asm("wfi");

        /* Write message to UART with current time. */
        uart_write_string("Loop at time ");
        uart_write_string(itoa(TIMER.TIMELR, itoa_result, 10));
        uart_write_string("\r\n");
    }

    /* Unreachable code. */
    return 0;
}

/**
 * Interrupt handler for Alarm 0.
 */
extern "C" void TIMER_IRQ_0_handler(void)
{
    /* Unlatch interrupt so it can fire again. Write 1 to clear, see Appendix A in the RP2040 datasheet.
     * If this is not done properly, the interrupt will keep triggering as fast as possible,
     * locking up the processor.
     */
    TIMER_CLEAR.INTR.ALARM_0 = 1u;
}
