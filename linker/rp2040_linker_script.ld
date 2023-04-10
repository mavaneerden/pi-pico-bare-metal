MEMORY
{
    Flash_second_stage(RX): ORIGIN = 0x10000000, LENGTH = 256 /* RP2040 loads 256 byte boot stage on startup, see section 2.8.1 in the RP2040 datasheet. */
    Flash(RX): ORIGIN = 0x10000000 + LENGTH(Flash_second_stage), LENGTH = 2M - LENGTH(Flash_second_stage) /* See section 2.6.3 in the RP2040 datasheet. The Pico uses a 2 MB flash, see Section 4.1 in the Pico datasheet. */
    SRAM(RWX): ORIGIN = 0x20000000, LENGTH = 0x40000 /* 256K, see section 2.6.2 in the RP2040 datasheet. */
    SRAM_core1(RWX): ORIGIN = 0x20040000, LENGTH = 4K /* SRAM memory bank 5, used for Core 1 stack. See section 2.6.2 in the RP2040 datasheet. */
    SRAM_core0(RWX): ORIGIN = 0x20041000, LENGTH = 4K /* SRAM memory bank 6, used for Core 0 stack. See section 2.6.2 in the RP2040 datasheet. */
}

ENTRY(rp2040_flash_second_stage) /* Begin the code at second stage boot loader. */

/* Useful documentation about sections: https://downloads.ti.com/docs/esd/SPRU513/introduction-to-sections-stdz0691509.html */
SECTIONS
{
    /* Section for the second stage boot loader. */
    .flash_second_stage :
    {
        KEEP(*(.flash_second_stage.entry_point))
        *(.flash_second_stage .flash_second_stage.*)
        . = 252; /* CRC starts after 252 bytes. See section 2.8.1.3.1 of the RP2040 datasheet. */
        LONG(0x43495045) /* CRC placeholder, will be overwritten by the bin2uf2 script. */
        . = ALIGN(4); /* Word alignment after section (not necessary as this section is always 256 bytes). */
    }> Flash_second_stage AT> Flash_second_stage

    /* Section for executable code. Copied from flash to SRAM by the second stage boot loader. */
    /* TODO: keep this in flash. */
    .text :
    {
        __text_start__ = .;
        KEEP(*(.vector_table)) /* Interrupt vector table. */
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

    /* Section for unitialized data. Initialized in the second stage boot loader. */
    .bss (NOLOAD) :
    {
        __bss_start__ = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4); /* Word alignment after section. */
        __bss_end__ = .;
    }> SRAM

    PROVIDE(__flash_text_start__ = LOADADDR(.text));
    PROVIDE(__flash_data_start__ = LOADADDR(.data));
}
