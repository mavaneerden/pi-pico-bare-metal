REGISTER_ATOMIC_XOR_OFFSET = 0x1000;
REGISTER_ATOMIC_SET_OFFSET = 0x2000;
REGISTER_ATOMIC_CLEAR_OFFSET = 0x3000;

/* Memory map. */
MEMORY
{
    XIP(RW): ORIGIN = 0x14000000, LENGTH = 0x3020 /* XIP peripheral, see section 2.6.3.6 in the RP2040 datasheet. */
    SSI(RW): ORIGIN = 0x18000000, LENGTH = 0x30FC /* SSI peripheral, see section 4.10.13 in the RP2040 datasheet. */
    SYSINFO(RW): ORIGIN = 0x40000000, LENGTH = 0x3044
    SYSCFG(RW): ORIGIN = 0x40004000, LENGTH = 0x301C
    CLOCKS(RW): ORIGIN = 0x40008000, LENGTH = 0x30C8 /* CLOCKS peripheral, see section 2.15.7 in the RP2040 datasheet. */
    RESETS(RW): ORIGIN = 0x4000C000, LENGTH = 0x300C /* RESETS peripheral, see section 2.14.3 in the RP2040 datasheet. */
    PSM(RW): ORIGIN = 0x40010000, LENGTH = 0x3010
    IO_BANK0(RW): ORIGIN = 0x40014000, LENGTH = 0x3190 /* IO_BANK0 peripheral, see section 2.19.6.1 in the RP2040 datasheet. */
    IO_QSPI(RW): ORIGIN = 0x40018000, LENGTH = 0x3058
    PADS_BANK0(RW): ORIGIN = 0x4001C000, LENGTH = 0x3084 /* PADS_BANK0 peripheral, see section 2.19.6.3 in the RP2040 datasheet. */
    PADS_QSPI(RW): ORIGIN = 0x40020000, LENGTH = 0x301C /* PADS_QSPI peripheral, see section 2.19.6.4 in the RP2040 datasheet. */
    XOSC(RW): ORIGIN = 0x40024000, LENGTH = 0x3020 /* XOSC peripheral, see section 2.16.7 in the RP2040 datasheet. */
    PLL_SYS(RW): ORIGIN = 0x40028000, LENGTH = 0x3010
    PLL_USB(RW): ORIGIN = 0x4002C000, LENGTH = 0x3010
    BUSCTRL(RW): ORIGIN = 0x40030000, LENGTH = 0x3028
    UART0(RW): ORIGIN = 0x40034000, LENGTH = 0x4000
    UART1(RW): ORIGIN = 0x40038000, LENGTH = 0x4000
    SPI0(RW): ORIGIN = 0x4003C000, LENGTH = 0x4000
    SPI1(RW): ORIGIN = 0x40040000, LENGTH = 0x4000
    I2C0(RW): ORIGIN = 0x40044000, LENGTH = 0x3100
    I2C1(RW): ORIGIN = 0x40048000, LENGTH = 0x3100
    ADC(RW): ORIGIN = 0x4004C000, LENGTH = 0x3024
    PWM(RW): ORIGIN = 0x40050000, LENGTH = 0x30B4
    TIMER(RW): ORIGIN = 0x40054000, LENGTH = 0x3044 /* TIMER peripheral, see section 4.6.5 in the RP2040 datasheet. */
    WATCHDOG(RW): ORIGIN = 0x40058000, LENGTH = 0x3030 /* WATCHDOG peripheral, see section 4.7.6 in the RP2040 datasheet. */
    RTC(RW): ORIGIN = 0x4005C000, LENGTH = 0x3030 /* RTC peripheral, see section 4.8.6 in the RP2040 datasheet. */
    ROSC(RW): ORIGIN = 0x40060000, LENGTH = 0x3024
    VREG_AND_CHIP_RESET(RW): ORIGIN = 0x40064000, LENGTH = 0x300C
    TBMAN(RW): ORIGIN = 0x40068000, LENGTH = 0x3004
    DMA(RW): ORIGIN = 0x50000000, LENGTH = 0x3AC8
    USBCTRL_DPRAM(RW): ORIGIN = 0x50100000, LENGTH = 0x3100
    USBCTRL_REGS(RW): ORIGIN = 0x50110000, LENGTH = 0x309C
    PIO0(RW): ORIGIN = 0x50200000, LENGTH = 0x3144
    PIO1(RW): ORIGIN = 0x50300000, LENGTH = 0x3144
    SIO(RW): ORIGIN = 0xD0000000, LENGTH = 0x180 /* SIO peripheral, see section 2.3.1.7 in the RP2040 datasheet. */
    PPB(RW): ORIGIN = 0xE0000000, LENGTH = 0xEDA4 /* M0+ NVIC peripheral, see section B3.2 in the ARMv6-M reference manual. */
}

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

    /* SYSINFO peripheral registers. */
    .registers.sysinfo (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.sysinfo)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.sysinfo.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.sysinfo.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.sysinfo.clear)
        . = ALIGN(4);
    }> SYSINFO

    /* SYSCFG peripheral registers. */
    .registers.syscfg (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.syscfg)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.syscfg.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.syscfg.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.syscfg.clear)
        . = ALIGN(4);
    }> SYSCFG

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

    /* PSM peripheral registers. */
    .registers.psm (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.psm)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.psm.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.psm.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.psm.clear)
        . = ALIGN(4);
    }> PSM

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

    /* IO_QSPI peripheral registers. */
    .registers.io_qspi (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.io_qspi)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.io_qspi.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.io_qspi.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.io_qspi.clear)
        . = ALIGN(4);
    }> IO_QSPI

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

    /* PLL_SYS peripheral registers. */
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

    /* PLL_USB peripheral registers. */
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

    /* BUSCTRL peripheral registers. */
    .registers.busctrl (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.busctrl)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.busctrl.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.busctrl.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.busctrl.clear)
        . = ALIGN(4);
    }> BUSCTRL

    /* UART0 peripheral registers. */
    .registers.uart0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.uart0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.uart0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.uart0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.uart0.clear)
        . = ALIGN(4);
    }> UART0

    /* UART1 peripheral registers. */
    .registers.uart1 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.uart1)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.uart1.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.uart1.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.uart1.clear)
        . = ALIGN(4);
    }> UART1

    /* SPI0 peripheral registers. */
    .registers.spi0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.spi0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.spi0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.spi0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.spi0.clear)
        . = ALIGN(4);
    }> SPI0

    /* SPI1 peripheral registers. */
    .registers.spi1 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.spi1)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.spi1.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.spi1.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.spi1.clear)
        . = ALIGN(4);
    }> SPI1

    /* I2C0 peripheral registers. */
    .registers.i2c0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.i2c0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.i2c0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.i2c0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.i2c0.clear)
        . = ALIGN(4);
    }> I2C0

    /* I2C1 peripheral registers. */
    .registers.i2c1 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.i2c1)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.i2c1.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.i2c1.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.i2c1.clear)
        . = ALIGN(4);
    }> I2C1

    /* ADC peripheral registers. */
    .registers.adc (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.adc)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.adc.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.adc.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.adc.clear)
        . = ALIGN(4);
    }> ADC

    /* PWM peripheral registers. */
    .registers.pwm (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pwm)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pwm.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pwm.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pwm.clear)
        . = ALIGN(4);
    }> PWM

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

    /* ROSC peripheral registers. */
    .registers.rosc (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.rosc)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.rosc.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.rosc.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.rosc.clear)
        . = ALIGN(4);
    }> ROSC

    /* VREG_AND_CHIP_RESET peripheral registers. */
    .registers.vreg_and_chip_reset (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.vreg_and_chip_reset)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.vreg_and_chip_reset.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.vreg_and_chip_reset.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.vreg_and_chip_reset.clear)
        . = ALIGN(4);
    }> VREG_AND_CHIP_RESET

    /* TBMAN peripheral registers. */
    .registers.tbman (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.tbman)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.tbman.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.tbman.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.tbman.clear)
        . = ALIGN(4);
    }> TBMAN

    /* DMA peripheral registers. */
    .registers.dma (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.dma)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.dma.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.dma.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.dma.clear)
        . = ALIGN(4);
    }> DMA

    /* USBCTRL_DPRAM peripheral registers. */
    .registers.usbctrl_dpram (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.usbctrl_dpram)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.usbctrl_dpram.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.usbctrl_dpram.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.usbctrl_dpram.clear)
        . = ALIGN(4);
    }> USBCTRL_DPRAM

    /* USBCTRL_REGS peripheral registers. */
    .registers.usbctrl_regs (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.usbctrl_regs)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.usbctrl_regs.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.usbctrl_regs.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.usbctrl_regs.clear)
        . = ALIGN(4);
    }> USBCTRL_REGS

    /* PIO0 peripheral registers. */
    .registers.pio0 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pio0)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pio0.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pio0.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pio0.clear)
        . = ALIGN(4);
    }> PIO0

    /* PIO1 peripheral registers. */
    .registers.pio1 (NOLOAD) :
    {
        __registers_start__ = .;
        *(.registers.pio1)
        . = __registers_start__ + REGISTER_ATOMIC_XOR_OFFSET;
        *(.registers.pio1.xor)
        . = __registers_start__ + REGISTER_ATOMIC_SET_OFFSET;
        *(.registers.pio1.set)
        . = __registers_start__ + REGISTER_ATOMIC_CLEAR_OFFSET;
        *(.registers.pio1.clear)
        . = ALIGN(4);
    }> PIO1

    .registers.sio (NOLOAD) :
    {
        *(.registers.sio*)
        . = ALIGN(4);
    }> SIO

    .registers.ppb (NOLOAD) :
    {
        *(.registers.ppb*)
        . = ALIGN(4);
    }> PPB
}
