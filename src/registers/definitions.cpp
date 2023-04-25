/**
 * Author:
 *   Marco van Eerden
 *
 * Description:
 *   Contains all registers and their memory sections. Also contains atomic register aliases for
 *   XOR, set and clear. Only RP2040-specific peripherals have these aliases, so Cortex-M0+ peripherals such as SIO and NVIC do not have them.
 *   The definitions need to be volatile, otherwise the compiler will optimise away crucial steps, such as setting a value to 0.
 */

#include "registers.hpp"

volatile CLOCKS_registers_t     CLOCKS              __attribute__((section(".registers.clocks")));
volatile CLOCKS_registers_t     CLOCKS_XOR          __attribute__((section(".registers.clocks.xor")));
volatile CLOCKS_registers_t     CLOCKS_SET          __attribute__((section(".registers.clocks.set")));
volatile CLOCKS_registers_t     CLOCKS_CLEAR        __attribute__((section(".registers.clocks.clear")));

volatile IO_BANK0_registers_t   IO_BANK0            __attribute__((section(".registers.io_bank0")));
volatile IO_BANK0_registers_t   IO_BANK0_XOR        __attribute__((section(".registers.io_bank0.xor")));
volatile IO_BANK0_registers_t   IO_BANK0_SET        __attribute__((section(".registers.io_bank0.set")));
volatile IO_BANK0_registers_t   IO_BANK0_CLEAR      __attribute__((section(".registers.io_bank0.clear")));

volatile NVIC_registers_t       NVIC                __attribute__((section(".registers.nvic")));

volatile PADS_BANK0_registers_t PADS_BANK0          __attribute__((section(".registers.pads_bank0")));
volatile PADS_BANK0_registers_t PADS_BANK0_XOR      __attribute__((section(".registers.pads_bank0.xor")));
volatile PADS_BANK0_registers_t PADS_BANK0_SET      __attribute__((section(".registers.pads_bank0.set")));
volatile PADS_BANK0_registers_t PADS_BANK0_CLEAR    __attribute__((section(".registers.pads_bank0.clear")));

volatile PADS_QSPI_registers_t  PADS_QSPI           __attribute__((section(".registers.pads_qspi")));
volatile PADS_QSPI_registers_t  PADS_QSPI_XOR       __attribute__((section(".registers.pads_qspi.xor")));
volatile PADS_QSPI_registers_t  PADS_QSPI_SET       __attribute__((section(".registers.pads_qspi.set")));
volatile PADS_QSPI_registers_t  PADS_QSPI_CLEAR     __attribute__((section(".registers.pads_qspi.clear")));

volatile RESETS_registers_t     RESETS              __attribute__((section(".registers.resets")));
volatile RESETS_registers_t     RESETS_XOR          __attribute__((section(".registers.resets.xor")));
volatile RESETS_registers_t     RESETS_SET          __attribute__((section(".registers.resets.set")));
volatile RESETS_registers_t     RESETS_CLEAR        __attribute__((section(".registers.resets.clear")));

volatile RTC_registers_t        RTC                 __attribute__((section(".registers.rtc")));
volatile RTC_registers_t        RTC_XOR             __attribute__((section(".registers.rtc.xor")));
volatile RTC_registers_t        RTC_SET             __attribute__((section(".registers.rtc.set")));
volatile RTC_registers_t        RTC_CLEAR           __attribute__((section(".registers.rtc.clear")));

volatile SIO_registers_t        SIO                 __attribute__((section(".registers.sio")));

volatile SSI_registers_t        SSI                 __attribute__((section(".registers.ssi")));
volatile SSI_registers_t        SSI_XOR             __attribute__((section(".registers.ssi.xor")));
volatile SSI_registers_t        SSI_SET             __attribute__((section(".registers.ssi.set")));
volatile SSI_registers_t        SSI_CLEAR           __attribute__((section(".registers.ssi.clear")));

volatile TIMER_registers_t      TIMER               __attribute__((section(".registers.timer")));
volatile TIMER_registers_t      TIMER_XOR           __attribute__((section(".registers.timer.xor")));
volatile TIMER_registers_t      TIMER_SET           __attribute__((section(".registers.timer.set")));
volatile TIMER_registers_t      TIMER_CLEAR         __attribute__((section(".registers.timer.clear")));

volatile WATCHDOG_registers_t   WATCHDOG            __attribute__((section(".registers.watchdog")));
volatile WATCHDOG_registers_t   WATCHDOG_XOR        __attribute__((section(".registers.watchdog.xor")));
volatile WATCHDOG_registers_t   WATCHDOG_SET        __attribute__((section(".registers.watchdog.set")));
volatile WATCHDOG_registers_t   WATCHDOG_CLEAR      __attribute__((section(".registers.watchdog.clear")));

volatile XIP_registers_t        XIP                 __attribute__((section(".registers.xip")));
volatile XIP_registers_t        XIP_XOR             __attribute__((section(".registers.xip.xor")));
volatile XIP_registers_t        XIP_SET             __attribute__((section(".registers.xip.set")));
volatile XIP_registers_t        XIP_CLEAR           __attribute__((section(".registers.xip.clear")));

volatile XOSC_registers_t       XOSC                __attribute__((section(".registers.xosc")));
volatile XOSC_registers_t       XOSC_XOR            __attribute__((section(".registers.xosc.xor")));
volatile XOSC_registers_t       XOSC_SET            __attribute__((section(".registers.xosc.set")));
volatile XOSC_registers_t       XOSC_CLEAR          __attribute__((section(".registers.xosc.clear")));
