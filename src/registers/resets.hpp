/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

union RESETS
{
    struct
    {
        uint32_t ADC : 1;
        uint32_t BUSCTRL : 1;
        uint32_t DMA : 1;
        uint32_t I2C0 : 1;
        uint32_t I2C1 : 1;
        uint32_t IO_BANK0 : 1;
        uint32_t IO_QSPI : 1;
        uint32_t JTAG : 1;
        uint32_t PADS_BANK0 : 1;
        uint32_t PADS_QSPI : 1;
        uint32_t PIO0 : 1;
        uint32_t PIO1 : 1;
        uint32_t PLL_SYS : 1;
        uint32_t PLL_USB : 1;
        uint32_t PWM : 1;
        uint32_t RTC : 1;
        uint32_t SPI0 : 1;
        uint32_t SPI1 : 1;
        uint32_t SYSCFG : 1;
        uint32_t SYSINFO : 1;
        uint32_t TBMAN : 1;
        uint32_t TIMER : 1;
        uint32_t UART0 : 1;
        uint32_t UART1 : 1;
        uint32_t USBCTRL : 1;
        uint32_t : 7;
    };
    uint32_t all;
};

typedef struct
{
    /**
     * Reset control. If a bit is set it means the peripheral is in reset. 0 means the peripheral’s reset is deasserted.
     * Write 0 to reset the peripheral.
     * Reset: 0x1 - Type: RW
     */
    union RESETS RESET;
    /* Watchdog select. If a bit is set then the watchdog will reset this peripheral when the watchdog fires.
     * Reset: 0x0 - Type: RW
     */
    union RESETS WDSEL;
    /* Reset done. If a bit is set then a reset done signal has been returned by the peripheral. This indicates that the
     * peripheral’s registers are ready to be accessed.
     * Reset: 0x0 - Type: RO
     */
    union RESETS RESET_DONE;
} RESETS_registers_t;

/* Reset controller registers. Normal read-write access. */
extern volatile RESETS_registers_t RESETS;
/* Reset controller registers. Atomic XOR on write. */
extern volatile RESETS_registers_t RESETS_XOR;
/* Reset controller registers. Atomic bitmask set on write. */
extern volatile RESETS_registers_t RESETS_SET;
/* Reset controller registers. Atomic bitmask clear on write. */
extern volatile RESETS_registers_t RESETS_CLEAR;
