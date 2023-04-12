#pragma once

#include <stdint.h>

enum SSI_CTRLR0_TMOD : uint8_t {
    SSI_CTRLR0_TMOD_BOTH_TX_AND_RX = 0x0,
    SSI_CTRLR0_TMOD_TX_ONLY = 0x1,
    SSI_CTRLR0_TMOD_RX_ONLY = 0x2,
    SSI_CTRLR0_TMOD_EEPROM_READ = 0x3
};

struct SSI_struct
{
    struct CTRLR0_struct
    {
        uint8_t DFS : 4;
        uint8_t FRF : 2;
        uint8_t SCPH : 1;
        uint8_t SCPOL : 1;
        enum SSI_CTRLR0_TMOD TMOD : 2;
        uint8_t SLV_OE : 1;
        uint8_t SRL : 1;
        uint8_t CFS : 4;
        uint8_t DFS_32 : 5;
        uint8_t SPI_FRF : 2;
        uint8_t : 1; /* RESERVED */
        uint8_t SSTE : 1;
        uint8_t : 7; /* RESERVED */
    } CTRLR0;

    struct CTRLR1_struct
    {
        uint16_t NDF : 16;
        uint16_t : 16;
    } CTRLR1;

    struct SSIENR_struct
    {
        uint8_t SSI_EN : 1;
        uint32_t : 31;
    } SSIENR;

    struct MWCR_struct
    {
        uint8_t MWMOD : 1;
        uint8_t MDD : 1;
        uint8_t MHS : 1;
        uint32_t : 29;
    } MWCR;

    uint8_t SER : 1;
    uint32_t : 31;

    struct BAUDR_struct
    {
        uint16_t SCKDV : 16;
        uint16_t : 16;
    } BAUDR;

    struct TXFTLR_struct
    {
        uint8_t TFT : 8;
        uint32_t : 24;
    } TXFTLR;

    struct RXFTLR_struct
    {
        uint8_t RFT : 8;
        uint32_t : 24;
    } RXFTLR;

    struct TXFLR_struct
    {
        uint8_t TFTFL : 8;
        uint32_t : 24;
    } TXFLR;

    struct RXFLR_struct
    {
        uint8_t RFTFL : 8;
        uint32_t : 24;
    } RXFLR;

    struct SR_struct
    {
        uint8_t BUSY : 1;
        uint8_t TFNF : 1;
        uint8_t TFE : 1;
        uint8_t RFNE : 1;
        uint8_t RFF : 1;
        uint8_t TXE : 1;
        uint8_t DCOL : 1;
        uint32_t : 25;
    } SR;

    struct IMR_struct
    {
        uint8_t TXEIM : 1;
        uint8_t TXOIM : 1;
        uint8_t RXUIM : 1;
        uint8_t RXOIM : 1;
        uint8_t RXFIM : 1;
        uint8_t MSTIM : 1;
        uint32_t : 26;
    } IMR;

    struct ISR_struct
    {
        uint8_t TXEIS : 1;
        uint8_t TXOIS : 1;
        uint8_t RXUIS : 1;
        uint8_t RXOIS : 1;
        uint8_t RXFIS : 1;
        uint8_t MSTIS : 1;
        uint32_t : 26;
    } ISR;

    struct RISR_struct
    {
        uint8_t TXEIR : 1;
        uint8_t TXOIR : 1;
        uint8_t RXUIR : 1;
        uint8_t RXOIR : 1;
        uint8_t RXFIR : 1;
        uint8_t MSTIR : 1;
        uint32_t : 26;
    } RISR;

    uint8_t TXOICR : 1;
    uint32_t : 31;

    uint8_t RXOICR : 1;
    uint32_t : 31;

    uint8_t RXUICR : 1;
    uint32_t : 31;

    uint8_t MSTICR : 1;
    uint32_t : 31;

    uint8_t ICR : 1;
    uint32_t : 31;

    struct DMACR_struct
    {
        uint8_t RDMAE : 1;
        uint8_t TDMAE : 1;
        uint32_t : 30;
    } DMACR;

    struct DMATDLR_struct
    {
        uint8_t DMATDL : 8;
        uint32_t : 24;
    } DMATDLR;

    struct DMARDLR_struct
    {
        uint8_t DMARDL : 8;
        uint32_t : 24;
    } DMARDLR;

    struct IDR_struct
    {
        uint32_t IDCODE;
    } IDR;

    struct SSI_VERSION_ID_struct
    {
        uint32_t SSI_COMP_VERSION;
    } SSI_VERSION_ID;

    struct DRx_struct
    {
        uint32_t DR;
    };
    struct DRx_struct DR0;
    struct DRx_struct DR1;
    struct DRx_struct DR2;
    struct DRx_struct DR3;
    struct DRx_struct DR4;
    struct DRx_struct DR5;
    struct DRx_struct DR6;
    struct DRx_struct DR7;
    struct DRx_struct DR8;
    struct DRx_struct DR9;
    struct DRx_struct DR10;
    struct DRx_struct DR11;
    struct DRx_struct DR12;
    struct DRx_struct DR13;
    struct DRx_struct DR14;
    struct DRx_struct DR15;
    struct DRx_struct DR16;
    struct DRx_struct DR17;
    struct DRx_struct DR18;
    struct DRx_struct DR19;
    struct DRx_struct DR20;
    struct DRx_struct DR21;
    struct DRx_struct DR22;
    struct DRx_struct DR23;
    struct DRx_struct DR24;
    struct DRx_struct DR25;
    struct DRx_struct DR26;
    struct DRx_struct DR27;
    struct DRx_struct DR28;
    struct DRx_struct DR29;
    struct DRx_struct DR30;
    struct DRx_struct DR31;
    struct DRx_struct DR32;
    struct DRx_struct DR33;
    struct DRx_struct DR34;
    struct DRx_struct DR35;

    struct RX_SAMPLE_DLY_struct
    {
        uint8_t RSD : 8;
        uint32_t : 24;
    } RX_SAMPLE_DLY;

    struct SPI_CTRLR0
    {
        uint8_t TRANS_TYPE : 2;
        uint8_t ADDR_L : 4;
        uint8_t : 2;
        uint8_t INST_L : 2;
        uint8_t : 1;
        uint8_t WAIT_CYCLES : 5;
        uint8_t SPI_DDR_EN : 1;
        uint8_t INST_DDR_EN : 1;
        uint8_t SPI_RSDS_EN : 1;
        uint8_t : 5;
        uint8_t XIP_CMD : 8;
    } SPI_CTRLR0;

    struct TXD_DRIVE_EDGE_struct
    {
        uint8_t TDE : 8;
        uint32_t : 24;
    } TXD_DRIVE_EDGE;
};

volatile struct SSI_struct SSI __attribute__((section(".registers.ssi")));
