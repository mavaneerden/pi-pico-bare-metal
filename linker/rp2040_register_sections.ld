REGISTER_ATOMIC_XOR_OFFSET = 0x1000;
REGISTER_ATOMIC_SET_OFFSET = 0x2000;
REGISTER_ATOMIC_CLEAR_OFFSET = 0x3000;

/* Memory map. */
MEMORY
{
    XIP(RW): ORIGIN = 0x14000000, LENGTH = 0x3020 /* XIP peripheral, see section 2.6.3.6 in the RP2040 datasheet. */
    SSI(RW): ORIGIN = 0x18000000, LENGTH = 0x30FC /* SSI peripheral, see section 4.10.13 in the RP2040 datasheet. */
    CLOCKS(RW): ORIGIN = 0x40008000, LENGTH = 0x30C8 /* CLOCKS peripheral, see section 2.15.7 in the RP2040 datasheet. */
    RESETS(RW): ORIGIN = 0x4000C000, LENGTH = 0x300C /* RESETS peripheral, see section 2.14.3 in the RP2040 datasheet. */
    IO_BANK0(RW): ORIGIN = 0x40014000, LENGTH = 0x3190 /* IO_BANK0 peripheral, see section 2.19.6.1 in the RP2040 datasheet. */
    PADS_BANK0(RW): ORIGIN = 0x4001C000, LENGTH = 0x3084 /* PADS_BANK0 peripheral, see section 2.19.6.3 in the RP2040 datasheet. */
    PADS_QSPI(RW): ORIGIN = 0x40020000, LENGTH = 0x301C /* PADS_QSPI peripheral, see section 2.19.6.4 in the RP2040 datasheet. */
    XOSC(RW): ORIGIN = 0x40024000, LENGTH = 0x3020 /* XOSC peripheral, see section 2.16.7 in the RP2040 datasheet. */
    PLL_SYS(RW): ORIGIN = 0x40028000, LENGTH = 0x3010 /* XOSC peripheral, see section 2.16.7 in the RP2040 datasheet. */
    PLL_USB(RW): ORIGIN = 0x4002c000, LENGTH = 0x3010 /* XOSC peripheral, see section 2.16.7 in the RP2040 datasheet. */
    UART0(RW): ORIGIN = 0x40034000, LENGTH = 0x4C /* UART0 peripheral, see section 4.2.8 in the RP2040 datasheet. */
    UART1(RW): ORIGIN = 0x40038000, LENGTH = 0x4C /* UART1 peripheral, see section 4.2.8 in the RP2040 datasheet. */
    TIMER(RW): ORIGIN = 0x40054000, LENGTH = 0x3044 /* TIMER peripheral, see section 4.6.5 in the RP2040 datasheet. */
    WATCHDOG(RW): ORIGIN = 0x40058000, LENGTH = 0x3030 /* WATCHDOG peripheral, see section 4.7.6 in the RP2040 datasheet. */
    RTC(RW): ORIGIN = 0x4005C000, LENGTH = 0x3030 /* RTC peripheral, see section 4.8.6 in the RP2040 datasheet. */
    SIO(RW): ORIGIN = 0xD0000000, LENGTH = 0x180 /* SIO peripheral, see section 2.3.1.7 in the RP2040 datasheet. */
    NVIC(RW): ORIGIN = 0xE000E100, LENGTH = 0xBFF /* M0+ NVIC peripheral, see section B3.2 in the ARMv6-M reference manual. */
}

/* Useful documentation about sections: https://downloads.ti.com/docs/esd/SPRU513/introduction-to-sections-stdz0691509.html */
SECTIONS
{
    /* XIP peripheral registers. */
    .registers.xip (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.xip)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.xip.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.xip.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.xip.clear)
        . = ALIGN(4);
    }> XIP

    /* SSI peripheral registers. */
    .registers.ssi (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.ssi)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.ssi.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.ssi.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.ssi.clear)
        . = ALIGN(4);
    }> SSI

    .registers.clocks (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.clocks)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.clocks.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.clocks.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.clocks.clear)
        . = ALIGN(4);
    }> CLOCKS

    .registers.resets (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.resets)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.resets.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.resets.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.resets.clear)
        . = ALIGN(4);
    }> RESETS

    .registers.io_bank0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.io_bank0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.io_bank0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.io_bank0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.io_bank0.clear)
        . = ALIGN(4);
    }> IO_BANK0

    .registers.pads_bank0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pads_bank0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pads_bank0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pads_bank0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pads_bank0.clear)
        . = ALIGN(4);
    }> PADS_BANK0

    .registers.pads_qspi (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pads_qspi)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pads_qspi.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pads_qspi.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pads_qspi.clear)
        . = ALIGN(4);
    }> PADS_QSPI

    .registers.xosc (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.xosc)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.xosc.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.xosc.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.xosc.clear)
        . = ALIGN(4);
    }> XOSC

    .registers.pll_sys (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pll_sys)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pll_sys.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pll_sys.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pll_sys.clear)
        . = ALIGN(4);
    }> PLL_SYS

    .registers.pll_usb (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pll_usb)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pll_usb.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pll_usb.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pll_usb.clear)
        . = ALIGN(4);
    }> PLL_USB

    .registers.uart0 (NOLOAD) :
    {
        *(.registers.uart0)
        . = ALIGN(4);
    }> UART0

    .registers.uart1 (NOLOAD) :
    {
        *(.registers.uart1)
        . = ALIGN(4);
    }> UART1

    .registers.timer (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.timer)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.timer.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.timer.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.timer.clear)
        . = ALIGN(4);
    }> TIMER

    .registers.watchdog (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.watchdog)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.watchdog.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.watchdog.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.watchdog.clear)
        . = ALIGN(4);
    }> WATCHDOG

    .registers.rtc (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.rtc)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.rtc.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.rtc.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.rtc.clear)
        . = ALIGN(4);
    }> RTC

    .registers.sio (NOLOAD) :
    {
        *(.registers.sio*)
        . = ALIGN(4);
    }> SIO

    .registers.nvic (NOLOAD) :
    {
        *(.registers.nvic*)
        . = ALIGN(4);
    }> NVIC
}
