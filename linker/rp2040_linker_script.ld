/* Size of the heap. */
HEAP_SIZE = 8K;

REGISTER_ATOMIC_XOR_OFFSET = 0x1000;
REGISTER_ATOMIC_SET_OFFSET = 0x2000;
REGISTER_ATOMIC_CLEAR_OFFSET = 0x3000;

/* Memory map. */
MEMORY
{
    Flash_second_stage(RX): ORIGIN = 0x10000000, LENGTH = 256 /* RP2040 loads 256 byte boot stage on startup, see section 2.8.1 in the RP2040 datasheet. */
    Flash(RX): ORIGIN = 0x10000000 + LENGTH(Flash_second_stage), LENGTH = 2M - LENGTH(Flash_second_stage) /* See section 2.6.3 in the RP2040 datasheet. The Pico uses a 2 MiB flash, see Section 4.1 in the Pico datasheet. */
    XIP(RW): ORIGIN = 0x14000000, LENGTH = 0x3020 /* XIP peripheral, see section 2.6.3.6 in the RP2040 datasheet. */
    SSI(RW): ORIGIN = 0x18000000, LENGTH = 0x30FC /* SSI peripheral, see section 4.10.13 in the RP2040 datasheet. */
    SRAM(RWX): ORIGIN = 0x20000000, LENGTH = 0x40000 /* 256 KiB, see section 2.6.2 in the RP2040 datasheet. */
    SRAM_core1(RWX): ORIGIN = 0x20040000, LENGTH = 4K /* SRAM memory bank 5, used for Core 1 stack. See section 2.6.2 in the RP2040 datasheet. */
    SRAM_core0(RWX): ORIGIN = 0x20041000, LENGTH = 4K /* SRAM memory bank 6, used for Core 0 stack. See section 2.6.2 in the RP2040 datasheet. */
    CLOCKS(RW): ORIGIN = 0x40008000, LENGTH = 0x30C8 /* CLOCKS peripheral, see section 2.15.7 in the RP2040 datasheet. */
    RESETS(RW): ORIGIN = 0x4000C000, LENGTH = 0x300C /* RESETS peripheral, see section 2.14.3 in the RP2040 datasheet. */
    IO_BANK0(RW): ORIGIN = 0x40014000, LENGTH = 0x3190 /* IO_BANK0 peripheral, see section 2.19.6.1 in the RP2040 datasheet. */
    PADS_BANK0(RW): ORIGIN = 0x4001C000, LENGTH = 0x3084 /* PADS_BANK0 peripheral, see section 2.19.6.3 in the RP2040 datasheet. */
    PADS_QSPI(RW): ORIGIN = 0x40020000, LENGTH = 0x301C /* PADS_QSPI peripheral, see section 2.19.6.4 in the RP2040 datasheet. */
    XOSC(RW): ORIGIN = 0x40024000, LENGTH = 0x3020 /* XOSC peripheral, see section 2.16.7 in the RP2040 datasheet. */
    TIMER(RW): ORIGIN = 0x40054000, LENGTH = 0x3044 /* TIMER peripheral, see section 4.6.5 in the RP2040 datasheet. */
    WATCHDOG(RW): ORIGIN = 0x40058000, LENGTH = 0x3030 /* WATCHDOG peripheral, see section 4.7.6 in the RP2040 datasheet. */
    RTC(RW): ORIGIN = 0x4005C000, LENGTH = 0x3030 /* RTC peripheral, see section 4.8.6 in the RP2040 datasheet. */
    SIO(RW): ORIGIN = 0xD0000000, LENGTH = 0x180 /* SIO peripheral, see section 2.3.1.7 in the RP2040 datasheet. */
    NVIC(RW): ORIGIN = 0xE000E100, LENGTH = 0xBFF /* M0+ NVIC peripheral, see section B3.2 in the ARMv6-M reference manual. */
}

ENTRY(rp2040_startup_flash_second_stage) /* Begin the code at second stage boot loader. */

/* Useful documentation about sections: https://downloads.ti.com/docs/esd/SPRU513/introduction-to-sections-stdz0691509.html */
SECTIONS
{
    /* Section for the second stage boot loader. */
    .flash_second_stage :
    {
        KEEP(*(.flash_second_stage.entry_point))
        . = 252; /* CRC starts after 252 bytes. See section 2.8.1.3.1 of the RP2040 datasheet. */
        LONG(0x43495045) /* CRC placeholder, will be overwritten by the bin2uf2 script. */
        /* LONG(3CA4C464) */
        /* LONG(0x64C4A43C) */
        . = ALIGN(4); /* Word alignment after section (not necessary as this section is always 256 bytes and starts at an already aligned address). */
    }> Flash_second_stage AT> Flash_second_stage

    /* .flash_second_stage_helpers :
    {
        KEEP(*(.vector_table))
        . = ALIGN(4);
    }> Flash */

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

    /* Section for executable code. Copied from flash to SRAM by the second stage boot loader. */
    /* TODO: keep this in flash. */
    .text :
    {
        __text_start__ = .;
        KEEP(*(.vector_table)) /* Interrupt vector table. Use KEEP to avoid dumping this section if it isn't used. */
        KEEP(*(.text.main))
        *(.text .text.*)
        *(.rodata .rodata.*)
        . = ALIGN(4); /* Word alignment after section. */
        __text_end__ = .;
    }> SRAM AT> Flash /* Normally this would be kept in flash. But since the flash on the Pico is external, it is easier to keep it in SRAM (see Section 2.8.1.3 in the RP2040 datasheet). */

    /* Section for initialized data. Copied from flash to SRAM by the second stage boot loader. */
    .data :
    {
        __data_start__ = .;
        *(.data .data.*)
        . = ALIGN(4); /* Word alignment after section. */
        __data_end__ = .;
    }> SRAM AT> Flash


    /* Section for unitialized data. Initialized to 0 in the second stage boot loader. */
    .bss :
    {
        __bss_start__ = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4); /* Word alignment after section. */
        __bss_end__ = .;
    }> SRAM

    /* Heap for dynamic allocation. */
    .heap (COPY):
    {
        __heap_start__ = .;
        . = . + HEAP_SIZE;
        . = ALIGN(4);
        __heap_end__ = .;
    }> SRAM

    /* Section for stack of core 1. Use COPY to not actually allocate this space so it can be used for something else if this core is not used: https://software-dl.ti.com/ccs/esd/documents/sdto_cgt_linker_special_section_types.html */
    .stack_core1 (COPY) :
    {
        . = . + LENGTH(SRAM_core1);
        . = ALIGN(4);
    }> SRAM_core1

    /* Allocation for stack of core 0. Do not use COPY because this is always used. */
    .stack_core0 :
    {
        . = . + LENGTH(SRAM_core0);
        . = ALIGN(4);
    }> SRAM_core0

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

    /* Define extra symbols for use in code. */
    __flash_text_start__ = LOADADDR(.text); /* Flash load address of .text section, used to copy to SRAM. */
    __flash_data_start__ = LOADADDR(.data); /* Flash load address of .data section, used to copy to SRAM. */
    __stack_1_top__ = ORIGIN(SRAM_core1) + LENGTH(SRAM_core1); /* Core 1 stack top. */
    __stack_1_bottom__ = ORIGIN(SRAM_core1); /* Core 1 stack bottom. */
    __stack_0_top__ = ORIGIN(SRAM_core0) + LENGTH(SRAM_core0); /* Core 0 stack top (Main Stack Pointer). */
    __stack_0_bottom__ = ORIGIN(SRAM_core0); /* Core 0 stack bottom. */
}
