/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include "rp2040_constants.hpp"

/* Default function (nothing). */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_NULL = 31u;

/*** SPI functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI0_RX = 1u; /* SPI0 receive. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI0_CSn = 1u; /* SPI0 chip select. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI0_SCK = 1u; /* SPI0 clock. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI0_TX = 1u; /* SPI0 transmit. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI1_RX = 1u; /* SPI1 receive. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI1_CSn = 1u; /* SPI1 chip select. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI1_SCK = 1u; /* SPI1 clock. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SPI1_TX = 1u; /* SPI1 transmit. */

/*** UART functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_TX = 2u; /* UART0 transmit. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_RX = 2u; /* UART0 receive. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_CTS = 2u; /* UART0 clear to send. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART0_RTS = 2u; /* UART0 ready to send. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART1_TX = 2u; /* UART1 transmit. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART1_RX = 2u; /* UART1 receive. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART1_CTS = 2u; /* UART1 clear to send. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_UART1_RTS = 2u; /* UART1 ready to send. */

/*** I2C functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_I2C0_SDA = 3u; /* I2C0 data. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_I2C0_SCL = 3u; /* I2C0 clock. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_I2C1_SDA = 3u; /* I2C1 data. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_I2C1_SCL = 3u; /* I2C1 clock. */

/*** PWM functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM0_A = 4u; /* PWM0 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM0_B = 4u; /* PWM0 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM1_A = 4u; /* PWM1 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM1_B = 4u; /* PWM1 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM2_A = 4u; /* PWM2 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM2_B = 4u; /* PWM2 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM3_A = 4u; /* PWM3 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM3_B = 4u; /* PWM3 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM4_A = 4u; /* PWM4 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM4_B = 4u; /* PWM4 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM5_A = 4u; /* PWM5 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM5_B = 4u; /* PWM5 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM6_A = 4u; /* PWM6 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM6_B = 4u; /* PWM6 channel B. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM7_A = 4u; /* PWM7 channel A. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PWM7_B = 4u; /* PWM7 channel B. */

/*** I/O functions. ***/

/* Software control of GPIO, from the single-cycle IO (SIO) block. The SIO function
 * must be selected for the processors to drive a GPIO, but the input is always connected,
 * so software can check the state of GPIOs at any time.
 */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_SIO = 5u;
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PIO0 = 6u; /* Programmable I/O block 0. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_PIO1 = 7u; /* Programmable I/O block 1. */

/*** CLOCK functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPIN0 = 8u; /* Clock input 0. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPOUT0 = 8u; /* Clock output 0. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPIN1 = 8u; /* Clock input 1. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPOUT1 = 8u; /* Clock output 1. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPOUT2 = 8u; /* Clock output 2. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_CLOCK_GPOUT3 = 8u; /* Clock output 3. */

/*** USB functions. ***/
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_USB_OVCUR_DET = 9u; /* USB VBUS overcurrent detection output, used to detect an overcurrent event. See section 4.1.2.8 in the RP2040 datasheet. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_USB_VBUS_DET = 9u; /* USB VBUS detect output, used to detect that VBUS is present in device mode. See section 4.1.2.8 in the RP2040 datasheet. */
constexpr uint32_t IOBANK0_GPIOx_CTRL_FUNCSEL_USB_VBUS_EN = 9u; /* USB VBUS enable input, used to enable VBUS in host mode. See section 4.1.2.8 in the RP2040 datasheet. */

enum IOBANK0_GPIOx_CTRL_OVERRIDE : uint8_t
{
    /* Do not override default behavior. */
    IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT = 0x0u,
    /* Invert default behavior. */
    IOBANK0_GPIOx_CTRL_OVERRIDE_INVERT = 0x1u,
    /* Drive the output/input/interrupt low, or disable output in case of OEOVER. */
    IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_LOW_OR_DISABLE = 0x2u,
    /* Drive the output/input/interrupt high, or enable output in case of OEOVER. */
    IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_HIGH_OR_ENABLE = 0x3u
};

typedef struct
{
    struct
    {
        union
        {
            struct
            {
                uint32_t : 8;
                /* Output signal from selected peripheral, before register override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t OUTFROMPERI : 1;
                /* Output signal to pad after register override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t OUTTOPAD : 1;
                uint32_t : 2;
                /* Output enable from selected peripheral, before register override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t OEFROMPERI : 1;
                /* Output enable to pad after register override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t OETOPAD : 1;
                uint32_t : 2;
                /* Input signal from pad before override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t INFROMPAD : 1;
                uint32_t : 1;
                /* Input signal from peripheral after override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t INTOPERI : 1;
                uint32_t : 4;
                /* Interrupt from pad before override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t IRQFROMPAD : 1;
                uint32_t : 1;
                /* Interrupt to processors after override is applied.
                 * Type: RO - Reset: 0x0
                 */
                uint32_t IRQTOPROC : 1;
                uint32_t : 5;
            };

            /* Contents of the entire 32-bit register. */
            uint32_t all;
        } STATUS;

        /* GPIO control including function select and overrides. */
        union
        {
            struct
            {
                /* Function select. 31 == NULL. See GPIO function table (section 2.19.2 in the RP2040 datasheet) for available functions.
                 * Can use one of the IOBANK0_GPIOx_CTRL_FUNCSEL_xxxx variables to set the pin function.
                 * Type: RW - Reset: 0x1f
                 */
                uint32_t FUNCSEL : 4;
                uint32_t : 3;
                /* Output override.
                 * Type: RW - Reset: 0x0
                 */
                enum IOBANK0_GPIOx_CTRL_OVERRIDE OUTOVER : 2;
                uint32_t : 2;
                /* Output enable override.
                 * Type: RW - Reset: 0x0
                 */
                enum IOBANK0_GPIOx_CTRL_OVERRIDE OEOVER : 2;
                uint32_t : 2;
                /* Input override.
                 * Type: RW - Reset: 0x0
                 */
                enum IOBANK0_GPIOx_CTRL_OVERRIDE INOVER : 2;
                uint32_t : 10;
                /* Interrupt override.
                 * Type: RW - Reset: 0x0
                 */
                enum IOBANK0_GPIOx_CTRL_OVERRIDE IRQOVER : 2;
                uint32_t : 2;
            } CTRL;

            /* Contents of the entire 32-bit register. */
            uint32_t all;
        };
    } GPIO[RP2040_NUMBER_OF_GPIO_PINS];

    // TODO: include all other registers.
} IO_BANK0_registers_t;

/* User Bank IO registers. Normal read-write access. */
extern volatile IO_BANK0_registers_t IO_BANK0;
/* User Bank IO registers. Atomic XOR on write. */
extern volatile IO_BANK0_registers_t IO_BANK0_XOR;
/* User Bank IO registers. Atomic bitmask set on write. */
extern volatile IO_BANK0_registers_t IO_BANK0_SET;
/* User Bank IO registers. Atomic bitmask clear on write. */
extern volatile IO_BANK0_registers_t IO_BANK0_CLEAR;
