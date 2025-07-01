/* Include memory sections for registers. Include directory specified by -L flag. */
/* INCLUDE rp2040_register_sections.ld */

/* Size of the heap. */
HEAP_SIZE = 4K;

/* Size of core 0 stack. Max size: 4096 bytes. */
STACK_SIZE_CORE0 = 2K;

/* Size of core 1 stack. Max size: 4096 bytes. */
STACK_SIZE_CORE1 = 2K;

/* Memory map. */
MEMORY
{
    Flash_second_stage(RX): ORIGIN = 0x10000000, LENGTH = 256 /* RP2040 loads 256 byte boot stage on startup, see section 2.8.1 in the RP2040 datasheet. */
    Flash(RX): ORIGIN = 0x10000000 + LENGTH(Flash_second_stage), LENGTH = 2M - LENGTH(Flash_second_stage) /* See section 2.6.3 in the RP2040 datasheet. The Pico uses a 2 MiB flash, see Section 4.1 in the Pico datasheet. */
    SRAM(RWX): ORIGIN = 0x20000000, LENGTH = 0x40000 /* 256 KiB, see section 2.6.2 in the RP2040 datasheet. */
    SRAM_core1(RWX): ORIGIN = 0x20040000, LENGTH = 4K /* SRAM memory bank 5, used for Core 1 stack. See section 2.6.2 in the RP2040 datasheet. */
    STACK_core1(RWX): ORIGIN = ORIGIN(SRAM_core1) + LENGTH(SRAM_core1) - STACK_SIZE_CORE1, LENGTH = STACK_SIZE_CORE1
    SRAM_core0(RWX): ORIGIN = 0x20041000, LENGTH = 4K /* SRAM memory bank 6, used for Core 0 stack. See section 2.6.2 in the RP2040 datasheet. */
    STACK_core0(RWX): ORIGIN = ORIGIN(SRAM_core0) + LENGTH(SRAM_core0) - STACK_SIZE_CORE0, LENGTH = STACK_SIZE_CORE0
}

ENTRY(rp2040_startup_flash_second_stage) /* Begin the code at second stage boot loader. */

/* Useful documentation about sections: https://downloads.ti.com/docs/esd/SPRU513/introduction-to-sections-stdz0691509.html */
SECTIONS
{
    /* Section for the second stage boot loader. */
    .flash_second_stage :
    {
        ld_bootloader_start = .;
        KEEP(*(.flash_second_stage.entry_point))
        . = 252; /* CRC starts after 252 bytes. See section 2.8.1.3.1 of the RP2040 datasheet. */
        LONG(0x5041494E) /* CRC placeholder, will be overwritten by the bin2uf2 script. */
        . = ALIGN(4); /* Word alignment after section (not necessary as this section is always 256 bytes and starts at an already-aligned address). */
        ld_bootloader_end = .;
    }> Flash_second_stage AT> Flash_second_stage

    ASSERT(ld_bootloader_start - ld_bootloader_end == 256, "ERROR: Pico second stage bootloader must be 256 bytes in size")

    /* Section for executable code. Copied from flash to SRAM by the second stage boot loader. */
    .text :
    {
        ld_text_start = .;
        KEEP(*(.text.main))
        *(.text .text.*)
        . = ALIGN(4); /* Word alignment after section. */
        ld_text_end = .;
    }> Flash

    .tors :
    {
        /* Array of pointers to functions to run before constructors. */
        ld_preinit_array_start = .;
        KEEP(*(SORT(.preinit_array.*)))
        KEEP(*(.preinit_array))
        ld_preinit_array_end = .;

        /* Array of pointers to constructors. */
        ld_init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        ld_init_array_end = .;

        /* Array of pointers to destructors. */
        ld_fini_array_start = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        ld_fini_array_end = .;

        . = ALIGN(4); /* Word alignment after section. */
    }> Flash

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
    }> FLASH

    /* Section for initialized data. Copied from flash to SRAM by the second stage boot loader. */
    .data :
    {
        ld_data_start = .;
        *(.data .data.*)
        . = ALIGN(4); /* Word alignment after section. */
        ld_data_end = .;
    }> SRAM AT> Flash


    /* Section for unitialized data. Initialized to 0 in the second stage boot loader. */
    .bss (NOLOAD) :
    {
        ld_bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4); /* Word alignment after section. */
        ld_bss_end = .;
    }> SRAM

    /* Heap for dynamic allocation. Must be at the END of SRAM! */
    .heap (COPY):
    {
        ld_heap_start = .;
        . = . + HEAP_SIZE;
        . = ALIGN(4);
        ld_heap_end = .;
    }> SRAM

    /* Section for stack of core 1. Use COPY to not actually allocate this space so it can be used for something else if this core is not used: https://software-dl.ti.com/ccs/esd/documents/sdto_cgt_linker_special_section_types.html */
    .stack_core1 (COPY) :
    {
        . = . + STACK_SIZE_CORE1;
        . = ALIGN(4);
    }> STACK_core1

    /* Allocation for stack of core 0. Do not use COPY because this is always used. */
    .stack_core0 :
    {
        . = . + STACK_SIZE_CORE0;
        . = ALIGN(4);
    }> STACK_core0

    /* Remove information from the standard libraries. TODO: do we want this? */
    /DISCARD/ :
    {
      libc.a ( * )
      libm.a ( * )
      libgcc.a ( * )
    }

    /* Assert stack size. */
    ASSERT(STACK_SIZE_CORE0 <= 4K, "Stack size for core 0 must be smaller than or equal to 4096 bytes.")
    ASSERT(STACK_SIZE_CORE1 <= 4K, "Stack size for core 1 must be smaller than or equal to 4096 bytes.")

    /* Define extra symbols for use in code. */
    ld_flash_text_start = LOADADDR(.text); /* Flash load address of .text section, used to copy to SRAM. */
    ld_flash_data_start = LOADADDR(.data); /* Flash load address of .data section, used to copy to SRAM. */
    ld_stack_1_top = ORIGIN(STACK_core1) + LENGTH(STACK_core1); /* Core 1 stack top. */
    ld_stack_1_bottom = ORIGIN(STACK_core1); /* Core 1 stack bottom. */
    ld_stack_0_top = ORIGIN(STACK_core0) + LENGTH(STACK_core0); /* Core 0 stack top (Main Stack Pointer). */
    ld_stack_0_bottom = ORIGIN(STACK_core0); /* Core 0 stack bottom. */
}
