/**
 * Author:
 *   Marco van Eerden
 *
 * Description:
 *   Blinks the LED every 0.5s using the TIMER peripheral and an interrupt.
 *   Uses raw register accesses.
 *
 *   Code inspired by https://github.com/mickey-happygolucky/PiPico-Baremetal/tree/main/blink_ram_timer
 */

#include "registers.hpp"
#include "rp2040_hal.hpp"

/* LED is on GPIO25. */
constexpr uint32_t LED_PIN = 25u;

/* Loop iteration duration. */
constexpr uint32_t ITERATION_DURATION_MICROSECONDS = 500 * 1000; /* 0.5s */

/**
 * Set up GPIO for blink.
 */
void gpio_setup(gpio::gpio_t& gpio)
{
    /* Reset the IO_BANK0 peripheral by clearing. Necessary, otherwise it does not work. */
    RESETS_CLEAR.RESET.IO_BANK0 = 1u;

    /* Wait until the IO_BANK0 peripheral has reset. */
    while (!RESETS.RESET_DONE.IO_BANK0);

    /* Set output override to default (no override). Using IO_BANK0_SET here does not work. */
    gpio.force_output_default();

    /* Set function to SIO. */
    gpio.set_function(IOBANK0_GPIOx_CTRL_FUNCSEL_SIO);

    /* Enable output for GPIO 25. */
    gpio.enable_output();
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
}

int main(void)
{
    gpio::gpio_t& led_gpio_pin = gpio::get_gpio(LED_PIN);

    /* Set up clocks for running timer. */
    clock_setup();

    /* Set up GPIO for LED blink. */
    gpio_setup(led_gpio_pin);

    /* Set up timer for blink interrupt. */
    timer_setup();

    /* Infinite loop. */
    while(true)
    {
        /* Get current time from timer (unsafe). ALARM only works with the lower timer part.
         * This lower part overflows so overflow of the sum below should have the same behaviour.
         */
        uint32_t time_of_next_iteration = TIMER.TIMELR + ITERATION_DURATION_MICROSECONDS;

        /* Toggle the LED pin. */
        led_gpio_pin.toggle_output();

        /* Configure Alarm 0 to fire at next iteration. */
        TIMER.ALARM0 = time_of_next_iteration;

        /* Sleep until interrupt occurs, see section A6.7.76 in the ARMv6-M architecture reference manual. */
        asm("wfi");
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
