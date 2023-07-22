/**
 * Author:
 *   Marco van Eerden
 *
 * Description:
 *   Contains all registers and their memory sections. Also contains atomic register aliases for
 *   XOR, SET and CLEAR. Only RP2040-specific peripherals have these aliases, so Cortex-M0+ peripherals such as SIO and PPB do not have them.
 *   The definitions need to be volatile, otherwise the compiler will optimise away crucial steps, such as setting a value to 0.
 */
#ifndef HALLELUJAH
#define HALLELUJAH

#include "CMSIS/rp2040_cmsis.h"

namespace rp2040::registers
{

static constexpr uintptr_t REGISTER_ATOMIC_XOR_OFFSET = 0x1000ul;
static constexpr uintptr_t REGISTER_ATOMIC_SET_OFFSET = 0x2000ul;
static constexpr uintptr_t REGISTER_ATOMIC_CLEAR_OFFSET = 0x3000ul;

extern "C" {

extern volatile XIP_CTRL_Type* XIP;
extern volatile XIP_CTRL_Type* XIP_XOR;
extern volatile XIP_CTRL_Type* XIP_SET;
extern volatile XIP_CTRL_Type* XIP_CLEAR;

extern volatile XIP_SSI_Type* XIP_SSI;
extern volatile XIP_SSI_Type* XIP_SSI_XOR;
extern volatile XIP_SSI_Type* XIP_SSI_SET;
extern volatile XIP_SSI_Type* XIP_SSI_CLEAR;

extern volatile SYSINFO_Type* SYSINFO;
extern volatile SYSINFO_Type* SYSINFO_XOR;
extern volatile SYSINFO_Type* SYSINFO_SET;
extern volatile SYSINFO_Type* SYSINFO_CLEAR;

extern volatile SYSCFG_Type* SYSCFG;
extern volatile SYSCFG_Type* SYSCFG_XOR;
extern volatile SYSCFG_Type* SYSCFG_SET;
extern volatile SYSCFG_Type* SYSCFG_CLEAR;

extern volatile CLOCKS_Type* CLOCKS;
extern volatile CLOCKS_Type* CLOCKS_XOR;
extern volatile CLOCKS_Type* CLOCKS_SET;
extern volatile CLOCKS_Type* CLOCKS_CLEAR;

extern volatile RESETS_Type* RESETS;
extern volatile RESETS_Type* RESETS_XOR;
extern volatile RESETS_Type* RESETS_SET;
extern volatile RESETS_Type* RESETS_CLEAR;

extern volatile PSM_Type* PSM;
extern volatile PSM_Type* PSM_XOR;
extern volatile PSM_Type* PSM_SET;
extern volatile PSM_Type* PSM_CLEAR;

extern volatile IO_BANK0_Type* IO_BANK0;
extern volatile IO_BANK0_Type* IO_BANK0_XOR;
extern volatile IO_BANK0_Type* IO_BANK0_SET;
extern volatile IO_BANK0_Type* IO_BANK0_CLEAR;

extern volatile IO_QSPI_Type* IO_QSPI;
extern volatile IO_QSPI_Type* IO_QSPI_XOR;
extern volatile IO_QSPI_Type* IO_QSPI_SET;
extern volatile IO_QSPI_Type* IO_QSPI_CLEAR;

extern volatile PADS_BANK0_Type* PADS_BANK0;
extern volatile PADS_BANK0_Type* PADS_BANK0_XOR;
extern volatile PADS_BANK0_Type* PADS_BANK0_SET;
extern volatile PADS_BANK0_Type* PADS_BANK0_CLEAR;

extern volatile PADS_QSPI_Type* PADS_QSPI;
extern volatile PADS_QSPI_Type* PADS_QSPI_XOR;
extern volatile PADS_QSPI_Type* PADS_QSPI_SET;
extern volatile PADS_QSPI_Type* PADS_QSPI_CLEAR;

extern volatile XOSC_Type* XOSC;
extern volatile XOSC_Type* XOSC_XOR;
extern volatile XOSC_Type* XOSC_SET;
extern volatile XOSC_Type* XOSC_CLEAR;

extern volatile PLL_SYS_Type* PLL_SYS;
extern volatile PLL_SYS_Type* PLL_SYS_XOR;
extern volatile PLL_SYS_Type* PLL_SYS_SET;
extern volatile PLL_SYS_Type* PLL_SYS_CLEAR;

extern volatile PLL_SYS_Type* PLL_USB;
extern volatile PLL_SYS_Type* PLL_USB_XOR;
extern volatile PLL_SYS_Type* PLL_USB_SET;
extern volatile PLL_SYS_Type* PLL_USB_CLEAR;

extern volatile BUSCTRL_Type* BUSCTRL;
extern volatile BUSCTRL_Type* BUSCTRL_XOR;
extern volatile BUSCTRL_Type* BUSCTRL_SET;
extern volatile BUSCTRL_Type* BUSCTRL_CLEAR;

extern volatile UART0_Type* UART0;
extern volatile UART0_Type* UART0_XOR;
extern volatile UART0_Type* UART0_SET;
extern volatile UART0_Type* UART0_CLEAR;

extern volatile UART0_Type* UART1;
extern volatile UART0_Type* UART1_XOR;
extern volatile UART0_Type* UART1_SET;
extern volatile UART0_Type* UART1_CLEAR;

extern volatile SPI0_Type* SPI0;
extern volatile SPI0_Type* SPI0_XOR;
extern volatile SPI0_Type* SPI0_SET;
extern volatile SPI0_Type* SPI0_CLEAR;

extern volatile SPI0_Type* SPI1;
extern volatile SPI0_Type* SPI1_XOR;
extern volatile SPI0_Type* SPI1_SET;
extern volatile SPI0_Type* SPI1_CLEAR;

extern volatile I2C0_Type* I2C0;
extern volatile I2C0_Type* I2C0_XOR;
extern volatile I2C0_Type* I2C0_SET;
extern volatile I2C0_Type* I2C0_CLEAR;

extern volatile I2C0_Type* I2C1;
extern volatile I2C0_Type* I2C1_XOR;
extern volatile I2C0_Type* I2C1_SET;
extern volatile I2C0_Type* I2C1_CLEAR;

extern volatile ADC_Type* ADC;
extern volatile ADC_Type* ADC_XOR;
extern volatile ADC_Type* ADC_SET;
extern volatile ADC_Type* ADC_CLEAR;

extern volatile PWM_Type* PWM;
extern volatile PWM_Type* PWM_XOR;
extern volatile PWM_Type* PWM_SET;
extern volatile PWM_Type* PWM_CLEAR;

extern volatile TIMER_Type* TIMER;
extern volatile TIMER_Type* TIMER_XOR;
extern volatile TIMER_Type* TIMER_SET;
extern volatile TIMER_Type* TIMER_CLEAR;

extern volatile WATCHDOG_Type* WATCHDOG;
extern volatile WATCHDOG_Type* WATCHDOG_XOR;
extern volatile WATCHDOG_Type* WATCHDOG_SET;
extern volatile WATCHDOG_Type* WATCHDOG_CLEAR;

extern volatile RTC_Type* RTC;
extern volatile RTC_Type* RTC_XOR;
extern volatile RTC_Type* RTC_SET;
extern volatile RTC_Type* RTC_CLEAR;

extern volatile ROSC_Type* ROSC;
extern volatile ROSC_Type* ROSC_XOR;
extern volatile ROSC_Type* ROSC_SET;
extern volatile ROSC_Type* ROSC_CLEAR;

extern volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET;
extern volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_XOR;
extern volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_SET;
extern volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_CLEAR;

extern volatile TBMAN_Type* TBMAN;
extern volatile TBMAN_Type* TBMAN_XOR;
extern volatile TBMAN_Type* TBMAN_SET;
extern volatile TBMAN_Type* TBMAN_CLEAR;

extern volatile DMA_Type* DMA;
extern volatile DMA_Type* DMA_XOR;
extern volatile DMA_Type* DMA_SET;
extern volatile DMA_Type* DMA_CLEAR;

extern volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM;
extern volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_XOR;
extern volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_SET;
extern volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_CLEAR;

extern volatile USBCTRL_REGS_Type* USBCTRL_REGS;
extern volatile USBCTRL_REGS_Type* USBCTRL_REGS_XOR;
extern volatile USBCTRL_REGS_Type* USBCTRL_REGS_SET;
extern volatile USBCTRL_REGS_Type* USBCTRL_REGS_CLEAR;

extern volatile PIO0_Type* PIO0;
extern volatile PIO0_Type* PIO0_XOR;
extern volatile PIO0_Type* PIO0_SET;
extern volatile PIO0_Type* PIO0_CLEAR;

extern volatile PIO0_Type* PIO1;
extern volatile PIO0_Type* PIO1_XOR;
extern volatile PIO0_Type* PIO1_SET;
extern volatile PIO0_Type* PIO1_CLEAR;

extern volatile SIO_Type* SIO;

extern volatile PPB_Type* PPB;
}

} // namespace rp2040::registers

#endif
