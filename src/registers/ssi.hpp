/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

// TODO: documentation!
// TODO: unions!

enum SSI_CTRLR0_TMOD_value : uint32_t
{
    SSI_CTRLR0_TMOD_BOTH_TX_AND_RX = 0x0u,
    SSI_CTRLR0_TMOD_TX_ONLY        = 0x1u,
    SSI_CTRLR0_TMOD_RX_ONLY        = 0x2u,
    SSI_CTRLR0_TMOD_EEPROM_READ    = 0x3u
};

/* Typedef is necessary, otherwise we get a 'pointer to incomplete class is not allowed' error. */
typedef struct
{
    struct
    {
        union
        {
            struct
            {
                uint32_t DFS : 4;
                uint32_t FRF : 2;
                uint32_t SCPH : 1;
                uint32_t SCPOL : 1;
                enum SSI_CTRLR0_TMOD_value TMOD : 2;
                uint32_t SLV_OE : 1;
                uint32_t SRL : 1;
                uint32_t CFS : 4;
                uint32_t DFS_32 : 5;
                uint32_t SPI_FRF : 2;
                uint32_t : 1; /* RESERVED */
                uint32_t SSTE : 1;
                uint32_t : 7; /* RESERVED */
            };
            uint32_t all;
        };
    } CTRLR0;

    struct
    {
        uint32_t NDF : 16;
        uint32_t : 16;
    } CTRLR1;

    struct
    {
        uint32_t SSI_EN : 1;
        uint32_t : 31;
    } SSIENR;

    struct
    {
        uint32_t MWMOD : 1;
        uint32_t MDD : 1;
        uint32_t MHS : 1;
        uint32_t : 29;
    } MWCR;

    uint32_t SER : 1;
    uint32_t : 31;

    struct
    {
        uint32_t SCKDV : 16;
        uint32_t : 16;
    } BAUDR;

    struct
    {
        uint32_t TFT : 8;
        uint32_t : 24;
    } TXFTLR;

    struct
    {
        uint32_t RFT : 8;
        uint32_t : 24;
    } RXFTLR;

    struct
    {
        uint32_t TFTFL : 8;
        uint32_t : 24;
    } TXFLR;

    struct
    {
        uint32_t RFTFL : 8;
        uint32_t : 24;
    } RXFLR;

    struct
    {
        uint32_t BUSY : 1;
        uint32_t TFNF : 1;
        uint32_t TFE : 1;
        uint32_t RFNE : 1;
        uint32_t RFF : 1;
        uint32_t TXE : 1;
        uint32_t DCOL : 1;
        uint32_t : 25;
    } SR;

    struct
    {
        uint32_t TXEIM : 1;
        uint32_t TXOIM : 1;
        uint32_t RXUIM : 1;
        uint32_t RXOIM : 1;
        uint32_t RXFIM : 1;
        uint32_t MSTIM : 1;
        uint32_t : 26;
    } IMR;

    struct
    {
        uint32_t TXEIS : 1;
        uint32_t TXOIS : 1;
        uint32_t RXUIS : 1;
        uint32_t RXOIS : 1;
        uint32_t RXFIS : 1;
        uint32_t MSTIS : 1;
        uint32_t : 26;
    } ISR;

    struct
    {
        uint32_t TXEIR : 1;
        uint32_t TXOIR : 1;
        uint32_t RXUIR : 1;
        uint32_t RXOIR : 1;
        uint32_t RXFIR : 1;
        uint32_t MSTIR : 1;
        uint32_t : 26;
    } RISR;

    uint32_t TXOICR : 1;
    uint32_t : 31;

    uint32_t RXOICR : 1;
    uint32_t : 31;

    uint32_t RXUICR : 1;
    uint32_t : 31;

    uint32_t MSTICR : 1;
    uint32_t : 31;

    uint32_t ICR : 1;
    uint32_t : 31;

    struct
    {
        uint32_t RDMAE : 1;
        uint32_t TDMAE : 1;
        uint32_t : 30;
    } DMACR;

    struct
    {
        uint32_t DMATDL : 8;
        uint32_t : 24;
    } DMATDLR;

    struct
    {
        uint32_t DMARDL : 8;
        uint32_t : 24;
    } DMARDLR;

    struct
    {
        uint32_t IDCODE;
    } IDR;

    struct
    {
        uint32_t SSI_COMP_VERSION;
    } SSI_VERSION_ID;

    struct DRx_struct
    {
        uint32_t DR;
    };
    struct DRx_struct DR[36];

    struct
    {
        uint32_t RSD : 8;
        uint32_t : 24;
    } RX_SAMPLE_DLY;

    struct
    {
        union
        {
            struct
            {
                uint32_t TRANS_TYPE : 2;
                uint32_t ADDR_L : 4;
                uint32_t : 2;
                uint32_t INST_L : 2;
                uint32_t : 1;
                uint32_t WAIT_CYCLES : 5;
                uint32_t SPI_DDR_EN : 1;
                uint32_t INST_DDR_EN : 1;
                uint32_t SPI_RSDS_EN : 1;
                uint32_t : 5;
                uint32_t XIP_CMD : 8;
            };
            uint32_t all;
        };
    } SPI_CTRLR0;

    struct
    {
        uint32_t TDE : 8;
        uint32_t : 24;
    } TXD_DRIVE_EDGE;
} SSI_registers_t;

extern volatile SSI_registers_t SSI;
extern volatile SSI_registers_t SSI_XOR;
extern volatile SSI_registers_t SSI_SET;
extern volatile SSI_registers_t SSI_CLEAR;
