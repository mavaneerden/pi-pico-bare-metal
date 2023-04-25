/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

typedef struct
{
    /* Value is 0 when read from processor core 0, and 1 when read from processor core 1.
     * Type: RO - Reset: N.A.
     */
    uint32_t CPUID : 1;
    uint32_t : 31;

    /* Input value for GPIO0...29.
     * Type: RO - Reset: 0x00000000
     */
    uint32_t GPIO_IN : 30;
    uint32_t : 2;

    /* Input value on QSPI IO in order 0...5: SCLK, SSn, SD0, SD1, SD2, SD3
     * Type: RO - Reset: 0x00
     */
    uint32_t GPIO_HI_IN : 6;
    uint32_t : 26;

    uint32_t : 32; /* Reserved register. */

    /* Set output level (1/0 → high/low) for GPIO0...29.
     * Reading back gives the last value written, NOT the input value from the pins.
     * If core 0 and core 1 both write to GPIO_OUT simultaneously (or to a
     * SET/CLR/XOR alias),
     * the result is as though the write from core 0 took place first,
     * and the write from core 1 was then applied to that intermediate result.
     * Type: RW - Reset: 0x00000000
     */
    uint32_t GPIO_OUT : 30;
    uint32_t : 2;

    /* Perform an atomic bit-set on GPIO_OUT, i.e. GPIO_OUT |= wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OUT_SET : 30;
    uint32_t : 2;

    /* Perform an atomic bit-clear on GPIO_OUT, i.e. GPIO_OUT &= ~wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OUT_CLR : 30;
    uint32_t : 2;

    /* Perform an atomic bitwise XOR on GPIO_OUT, i.e. GPIO_OUT ^= wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OUT_XOR : 30;
    uint32_t : 2;

    /* Set output enable (1/0 → output/intput) for GPIO0...29.
     * Reading back gives the last value written.
     * If core 0 and core 1 both write to GPIO_OUT simultaneously (or to a
     * SET/CLR/XOR alias),
     * the result is as though the write from core 0 took place first,
     * and the write from core 1 was then applied to that intermediate result.
     * Type: RW - Reset: 0x00000000
     */
    uint32_t GPIO_OE : 30;
    uint32_t : 2;

    /* Perform an atomic bit-set on GPIO_OE, i.e. GPIO_OE |= wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OE_SET : 30;
    uint32_t : 2;

    /* Perform an atomic bit-clear on GPIO_OE, i.e. GPIO_OE &= ~wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OE_CLR : 30;
    uint32_t : 2;

    /* Perform an atomic bitwise XOR on GPIO_OE, i.e. GPIO_OE ^= wdata.
     * Type: WO - Reset: 0x00000000
     */
    uint32_t GPIO_OE_XOR : 30;
    uint32_t : 2;

    // TODO: add more registers.
} SIO_registers_t;

/* Single-cycle Input/Output peripheral. SIO does not support atomic register operations directly. */
extern volatile SIO_registers_t SIO;
