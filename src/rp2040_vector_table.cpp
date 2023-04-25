/**
 * Author:
 *   Marco van Eerden
 * Description:
 *   Contains the interrupt vector table and default interrupt handlers.
 *   The default handlers have the 'weak' attribute, which tells the linker that
 *   it should prioritize other implementations over this one.
 *   This is nice because the user can overwrite the default implementations easily.
 */

// #include <stdint.h>
#include "rp2040_vector_table.hpp"

/* Attribute used for default interrupt handlers.
 * - weak: tells linker that definition can be overwritten.
 * - noreturn: tells compiler that function does not return.
 * - alias: used default_handler as default definition.
 * - interrupt: tells the compiler that this function is an interrupt.
 */
#define DEFAULT_HANDLER_ATTRIBUTE __attribute__((weak, noreturn, alias("default_handler"), interrupt("IRQ")))

/* Pointer to the top of the stack. */
extern uint32_t __stack_0_top__;

#ifdef __cplusplus
extern "C" { /* Required to avoid name mangling for weak functions. */
#endif

/******** CORTEX M0+ INTERRUPT HANDLERS ********/
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


#ifdef __cplusplus
}
#endif

/******** INTERRUPT VECTOR TABLE ********/
/* See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table.
 * Contains the main stack pointer and all interrupt handlers.
 *
 * We add it to its own section so we can link it later. This is not strictly necessary because the
 * VTOR register contains the address of the interrupt vector table: it does not need to be in a specific place.
 */
void* interrupt_vector_table[RP2040_VECTOR_TABLE_SIZE] __attribute__((section(".vector_table"))) = {
    (void*) &__stack_0_top__,
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
