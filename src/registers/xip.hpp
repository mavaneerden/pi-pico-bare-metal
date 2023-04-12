#pragma once

#include <stdint.h>

struct XIP_struct
{
    /* Cache control. */
    struct CTRL_Struct
    {
        /* When 1, enable the cache. When the cache is disabled, all XIP accesses will go straight to the flash,
            * without querying the cache. When enabled, cacheable XIP accesses will query the cache,
            * and the flash will not be accessed if the tag matches and the valid bit is set.
            * If the cache is enabled, cache-as-SRAM accesses have no effect on the cache data RAM, and will produce a bus error response.
            * RESET: 0x1
            */
        uint8_t EN : 1;
        /* When 1, writes to any alias other than 0x0 (caching, allocating) will produce a bus fault.
        * When 0, these writes are silently ignored.
        * In either case, writes to the 0x0 alias will deallocate on tag match, as usual.
        * RESET: 0x1
        */
        uint8_t ERR_BADWRITE : 1;
        uint8_t : 1; /* RESERVED */
        /* When 1, the cache memories are powered down. They retain state, but can not be accessed.
        * This reduces static power dissipation. Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache cannot be enabled when powered down.
        * Cache-as-SRAM accesses will produce a bus error response when the cache is powered down.
        * RESET: 0x0
        */
        uint8_t POWER_DOWN : 1;
        uint32_t : 28; /* RESERVED */
    } CTRL;

    /* Cache Flush control.
     * Write 1 to flush the cache. This clears the tag memory, but the data memory retains its contents.
     * (This means cache-as-SRAM contents is not affected by flush or reset.)
     * Reading will hold the bus (stall the processor) until the flush completes.
     * Alternatively STAT can be polled until completion.
     * RESET: 0x0
     */
    uint8_t FLUSH : 1;
    uint32_t : 31; /* RESERVED */

    /* Cache Status. */
    struct STAT_Struct
    {
        /* Reads as 0 while a cache flush is in progress, and 1 otherwise.
            * The cache is flushed whenever the XIP block is reset, and also when requested via the FLUSH register.
            * RESET: 0x0
            */
        uint8_t FLUSH_READY : 1;
        /* When 1, indicates the XIP streaming FIFO is completely empty.
            * RESET: 0x1
            */
        uint8_t FIFO_EMPTY : 1;
        /* When 1, indicates the XIP streaming FIFO is completely full.
            * The streaming FIFO is 2 entries deep, so the full and empty flag allow its level to be ascertained.
            * RESET: 0x0
            */
        uint8_t FIFO_FULL : 1;
        uint32_t : 29; /* RESERVED */
    } STAT;

    /* Cache Hit counter.
     * A 32 bit saturating counter that increments upon each cache hit, i.e. when an XIP access is serviced directly from cached data.
     * Write any value to clear.
     * RESET: 0x00000000
     */
    uint32_t CTR_HIT;

    /* Cache Access counter.
     * A 32 bit saturating counter that increments upon each XIP access, whether the cache is hit or not.
     * This includes noncacheable accesses. Write any value to clear.
     * RESET: 0x00000000
     */
    uint32_t CTR_ACC;

    uint8_t : 2; /* RESERVED */
    /* FIFO stream address.
     * The address of the next word to be streamed from flash to the streaming FIFO.
     * Increments automatically after each flash access.
     * Write the initial access address here before starting a streaming read.
     * RESET: 0x00000000
     */
    uint32_t STREAM_ADDR : 30;

    /* FIFO stream control.
     * Write a nonzero value to start a streaming read.
     * This will then progress in the background, using flash idle cycles to transfer a linear data block from flash to the streaming FIFO.
     * Decrements automatically (1 at a time) as the stream progresses, and halts on reaching 0.
     * Write 0 to halt an in-progress stream, and discard any in-flight read, so that a new stream can immediately be started (after draining the FIFO and reinitialising STREAM_ADDR).
     * RESET: 0x000000
     */
    uint32_t STREAM_CTR : 22;
    uint16_t : 10; /* RESERVED */

    /* FIFO stream data.
     * Streamed data is buffered here, for retrieval by the system DMA.
     * This FIFO can also be accessed via the XIP_AUX slave, to avoid exposing the DMA to bus stalls caused by other XIP traffic.
     * RESET: 0x00000000
     */
    uint32_t STREAM_FIFO;
};

/* Execute-in-place (XIP) control registers. */
volatile struct XIP_struct XIP __attribute__((section(".registers.xip")));
