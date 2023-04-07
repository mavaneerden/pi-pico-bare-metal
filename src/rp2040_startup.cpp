/**
 * Author:
 *   Marco van Eerden
 * Description:
 *   Contains the interrupt vector table and default interrupt handlers.
 *   The default handlers have the 'weak' attribute, which tells the linker that
 *   it should prioritize other implementations over this one.
 *   This is nice because the user can overwrite the default implementations easily.
 */

#include <stdint.h>

/* Attribute used for default interrupt handlers. */
#define DEFAULT_HANDLER_ATTRIBUTE __attribute__((weak, alias("default_handler")))

/* Number of IRQs on the RP2040. See RP2040 data sheet, section 2.3.2.
 * The RP2040 supports all 32 possible external interrupts by setting values in the NVIC, but only 26 are actually implemented in the hardware.
 */
constexpr uint8_t RP2040_NUM_INTERRUPTS = 26u;

/* Interrupt vector size.
 * See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 */
constexpr uint8_t CORTEX_M0PLUS_INTERRUPT_VECTOR_SIZE = 0x4u;

/* Initial size of vector table, includes all negative IRQ numbered exceptions.
 * See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 */
constexpr uint8_t CORTEX_M0PLUS_VECTOR_TABLE_INITIAL_SIZE = 0x40u;

/* Vector table start address.
 * See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 */
constexpr uint32_t CORTEX_M0PLUS_VECTOR_TABLE_ADDRESS_START = 0x00000000u;

/* Calculated vector table size. */
constexpr uint8_t RP2040_VECTOR_TABLE_SIZE = CORTEX_M0PLUS_VECTOR_TABLE_INITIAL_SIZE + (CORTEX_M0PLUS_INTERRUPT_VECTOR_SIZE * RP2040_NUM_INTERRUPTS);

/* Reset value of the Main Stack Pointer (MSP). See Table B3-1 in the ARMv6-M Architecture Reference manual. */
constexpr uint32_t SP_main = 0x40000000u;


/******** CORTEX M0+ INTERRUPT HANDLERS ********/
extern "C" { /* Necessary to avoid name mangling. */

/**
 * Default interrupt handler. Called whenever an interrupt happens and
 * it is not overwritten. Enters an infinite hold.
 */
void default_handler(void)
{
    while (true);
}

/**
 * Reset handler. Called when board is powered on or locally reset.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: -3.
 */
void Reset_handler(void) DEFAULT_HANDLER_ATTRIBUTE;

/**
 * Non-Maskable Interrupt (NMI) handler. Called when an NMI interrupt is generated.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: -2.
 */
void NMI_handler(void) DEFAULT_HANDLER_ATTRIBUTE;

/**
 * HardFault handler. Called when a fault occurs that is not handled by other exception mechanisms.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: -1.
 */
void HardFault_handler(void) DEFAULT_HANDLER_ATTRIBUTE;

/**
 * Supervisor Call (SVCall) handler. Called on execution of the SVC instruction.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: configurable via SHPR2.PRI_11.
 */
void SVCall_handler(void) DEFAULT_HANDLER_ATTRIBUTE;

/**
 * Pending Supervisor Call (PendSV) handler. Called when ICSR.PENDSVSET is set by software.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: configurable via SHPR3.PRI_14.
 */
void PendSV_handler(void) DEFAULT_HANDLER_ATTRIBUTE;

/**
 * System timer handler. Called when the system timer generates an interrupt.
 * See section B1.5.1 of the ARMv6-M Architecture Reference Manual.
 * Priority: configurable via SHPR3.PRI_15.
 */
void SysTick_handler(void) DEFAULT_HANDLER_ATTRIBUTE;


/******** RP2040 INTERRUPT HANDLERS ********/
/* See section 2.3.2 in RP2040 Datasheet. */
void TIMER_IRQ_0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void TIMER_IRQ_1_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void TIMER_IRQ_2_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void TIMER_IRQ_3_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void PWM_IRQ_WRAP_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void USBCTRL_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void XIP_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void PIO0_IRQ_0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void PIO0_IRQ_1_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void PIO1_IRQ_0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void PIO1_IRQ_1_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void DMA_IRQ_0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void DMA_IRQ_1_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void IO_IRQ_BANK0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void IO_IRQ_QSPI_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void SIO_IRQ_PROC0_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void SIO_IRQ_PROC1_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void CLOCKS_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void SPI0_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void SPI1_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void UART0_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void UART1_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void ADC_IRQ_FIFO_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void I2C0_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void I2C1_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;
void RTC_IRQ_handler(void) DEFAULT_HANDLER_ATTRIBUTE;


/******** INTERRUPT VECTOR TABLE ********/
/* See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 * For some reason, using 'void* const' removes the section. Adding 'extern "C"' makes it work again, but it is already inside an extern "C"?
 * Adding this extra 'const' at the end would make it a READONLY section.
 * We add it to its own section so we can link it later. This is not strictly necessary because the
 * VTOR register contains the address of the interrupt vector table: it does not need to be in a specific place.
 */
const volatile void* interrupt_vector_table[RP2040_VECTOR_TABLE_SIZE] __attribute__((section(".isr_vector"))) = {
    (void*) SP_main,
    (void*) &Reset_handler,
    (void*) &NMI_handler,
    (void*) &HardFault_handler,
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    (void*) &SVCall_handler,
    nullptr, /* Reserved. */
    nullptr, /* Reserved. */
    (void*) &PendSV_handler,
    (void*) &SysTick_handler,
    (void*) &TIMER_IRQ_0_handler,
    (void*) &TIMER_IRQ_1_handler,
    (void*) &TIMER_IRQ_2_handler,
    (void*) &TIMER_IRQ_3_handler,
    (void*) &PWM_IRQ_WRAP_handler,
    (void*) &USBCTRL_IRQ_handler,
    (void*) &XIP_IRQ_handler,
    (void*) &PIO0_IRQ_0_handler,
    (void*) &PIO0_IRQ_1_handler,
    (void*) &PIO1_IRQ_0_handler,
    (void*) &PIO1_IRQ_1_handler,
    (void*) &DMA_IRQ_0_handler,
    (void*) &DMA_IRQ_1_handler,
    (void*) &IO_IRQ_BANK0_handler,
    (void*) &IO_IRQ_QSPI_handler,
    (void*) &SIO_IRQ_PROC0_handler,
    (void*) &SIO_IRQ_PROC1_handler,
    (void*) &CLOCKS_IRQ_handler,
    (void*) &SPI0_IRQ_handler,
    (void*) &SPI1_IRQ_handler,
    (void*) &UART0_IRQ_handler,
    (void*) &UART1_IRQ_handler,
    (void*) &ADC_IRQ_FIFO_handler,
    (void*) &I2C0_IRQ_handler,
    (void*) &I2C1_IRQ_handler,
    (void*) &RTC_IRQ_handler
};
}