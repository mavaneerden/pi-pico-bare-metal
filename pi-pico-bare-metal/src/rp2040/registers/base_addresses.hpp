#pragma once

#include "types.hpp"

namespace rp2040::registers::base_addresses
{

static constexpr hw_register_address_t XIP                 = 0x14000000U;
static constexpr hw_register_address_t SSI                 = 0x18000000U;
static constexpr hw_register_address_t SYSINFO             = 0x40000000U;
static constexpr hw_register_address_t SYSCFG              = 0x40004000U;
static constexpr hw_register_address_t CLOCKS              = 0x40008000U;
static constexpr hw_register_address_t RESETS              = 0x4000C000U;
static constexpr hw_register_address_t PSM                 = 0x40010000U;
static constexpr hw_register_address_t IO_BANK0            = 0x40014000U;
static constexpr hw_register_address_t IO_QSPI             = 0x40018000U;
static constexpr hw_register_address_t PADS_BANK0          = 0x4001C000U;
static constexpr hw_register_address_t PADS_QSPI           = 0x40020000U;
static constexpr hw_register_address_t XOSC                = 0x40024000U;
static constexpr hw_register_address_t PLL_SYS             = 0x40028000U;
static constexpr hw_register_address_t PLL_USB             = 0x4002C000U;
static constexpr hw_register_address_t BUSCTRL             = 0x40030000U;
static constexpr hw_register_address_t UART0               = 0x40034000U;
static constexpr hw_register_address_t UART1               = 0x40038000U;
static constexpr hw_register_address_t SPI0                = 0x4003C000U;
static constexpr hw_register_address_t SPI1                = 0x40040000U;
static constexpr hw_register_address_t I2C0                = 0x40044000U;
static constexpr hw_register_address_t I2C1                = 0x40048000U;
static constexpr hw_register_address_t ADC                 = 0x4004C000U;
static constexpr hw_register_address_t PWM                 = 0x40050000U;
static constexpr hw_register_address_t TIMER               = 0x40054000U;
static constexpr hw_register_address_t WATCHDOG            = 0x40058000U;
static constexpr hw_register_address_t RTC                 = 0x4005C000U;
static constexpr hw_register_address_t ROSC                = 0x40060000U;
static constexpr hw_register_address_t VREG_AND_CHIP_RESET = 0x40064000U;
static constexpr hw_register_address_t TBMAN               = 0x40068000U;
static constexpr hw_register_address_t DMA                 = 0x50000000U;
static constexpr hw_register_address_t USBCTRL_DPRAM       = 0x50100000U;
static constexpr hw_register_address_t USBCTRL_REGS        = 0x50110000U;
static constexpr hw_register_address_t PIO0                = 0x50200000U;
static constexpr hw_register_address_t PIO1                = 0x50300000U;
static constexpr hw_register_address_t SIO                 = 0xD0000000U;
static constexpr hw_register_address_t PPB                 = 0xE0000000U;

}  // namespace rp2040::registers::base_addresses
