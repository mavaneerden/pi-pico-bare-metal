/**
 * Author:
 *   Marco van Eerden
 * Description:
 */

#pragma once

#include <stdint.h>

typedef struct
{
    /* Data Register. */
    union
    {
        struct
        {
            /* Receive (read) data character. Transmit (write) data character.
             *
             * Type: RWF
             */
            uint32_t DATA : 8;
            /* Framing error. When set to 1, it indicates that the received
             * character did not have a valid stop bit (a valid stop bit is 1).
             * In FIFO mode, this error is associated with the
             * character at the top of the FIFO.
             *
             * Type: RO
             */
            uint32_t FE : 1;
            /* Parity error. When set to 1, it indicates that the parity of
             * the received data character does not match the parity that
             * the EPS and SPS bits in the Line Control Register,
             * UARTLCR_H. In FIFO mode, this error is associated with
             * the character at the top of the FIFO.
             *
             * Type: RO
             */
            uint32_t PE : 1;
            /* Break error. This bit is set to 1 if a break condition was
             * detected, indicating that the received data input was held
             * LOW for longer than a full-word transmission time
             * (defined as start, data, parity and stop bits). In FIFO mode,
             * this error is associated with the character at the top of the
             * FIFO. When a break occurs, only one 0 character is loaded
             * into the FIFO. The next character is only enabled after the
             * receive data input goes to a 1 (marking state), and the
             * next valid start bit is received.
             *
             * Type: RO
             */
            uint32_t BE : 1;
            /* Overrun error. This bit is set to 1 if data is received and the
             * receive FIFO is already full. This is cleared to 0 once there
             * is an empty space in the FIFO and a new character can be
             * written to it.
             *
             * Type: RO
             */
            uint32_t OE : 1;
            uint32_t : 20;
        };
        /* All register bits. */
        uint32_t all;
    } UARTDR;

    /* Receive Status Register/Error Clear Register. */
    union
    {
        struct
        {
            /* Framing error. When set to 1, it indicates that the received
             * character did not have a valid stop bit (a valid stop bit is
             * 1). This bit is cleared to 0 by a write to UARTECR. In FIFO
             * mode, this error is associated with the character at the top
             * of the FIFO.
             *
             * Type: WC
             * Reset: 0x0
             */
            uint32_t FE : 1;
            /* Parity error. When set to 1, it indicates that the parity of
             * the received data character does not match the parity that
             * the EPS and SPS bits in the Line Control Register,
             * UARTLCR_H. This bit is cleared to 0 by a write to
             * UARTECR. In FIFO mode, this error is associated with the
             * character at the top of the FIFO.
             *
             * Type: WC
             * Reset: 0x0
             */
            uint32_t PE : 1;
            /* Break error. This bit is set to 1 if a break condition was
             * detected, indicating that the received data input was held
             * LOW for longer than a full-word transmission time
             * (defined as start, data, parity, and stop bits). This bit is
             * cleared to 0 after a write to UARTECR. In FIFO mode, this
             * error is associated with the character at the top of the
             * FIFO. When a break occurs, only one 0 character is loaded
             * into the FIFO. The next character is only enabled after the
             * receive data input goes to a 1 (marking state) and the next
             * valid start bit is received.
             *
             * Type: WC
             * Reset: 0x0
             */
            uint32_t BE : 1;
            /* Overrun error. This bit is set to 1 if data is received and the
             * FIFO is already full. This bit is cleared to 0 by a write to
             * UARTECR. The FIFO contents remain valid because no
             * more data is written when the FIFO is full, only the
             * contents of the shift register are overwritten. The CPU
             * must now read the data, to empty the FIFO.
             *
             * Type: WC
             * Reset: 0x0
             */
            uint32_t OE : 1;
            uint32_t : 28;
        };
        /* All register bits. */
        uint32_t all;
    } UARTRSR;

    uint32_t __reserved0[4];

    /* Flag Register. */
    union
    {
        struct
        {
            /* Clear to send. This bit is the complement of the UART
             * clear to send, nUARTCTS, modem status input. That is, the
             * bit is 1 when nUARTCTS is LOW.
             *
             * Type: RO
             */
            uint32_t CTS : 1;
            /* Data set ready. This bit is the complement of the UART
             * data set ready, nUARTDSR, modem status input. That is,
             * the bit is 1 when nUARTDSR is LOW.
             *
             * Type: RO
             */
            uint32_t DSR : 1;
            /* Data carrier detect. This bit is the complement of the
             * UART data carrier detect, nUARTDCD, modem status
             * input. That is, the bit is 1 when nUARTDCD is LOW.
             *
             * Type: RO
             */
            uint32_t DCD : 1;
            /* UART busy. If this bit is set to 1, the UART is busy
             * transmitting data. This bit remains set until the complete
             * byte, including all the stop bits, has been sent from the
             * shift register. This bit is set as soon as the transmit FIFO
             * becomes non-empty, regardless of whether the UART is
             * enabled or not.
             *
             * Type: RO
             * Resest: 0x0
             */
            uint32_t BUSY : 1;
            /* Receive FIFO empty. The meaning of this bit depends on
             * the state of the FEN bit in the UARTLCR_H Register. If the
             * FIFO is disabled, this bit is set when the receive holding
             * register is empty. If the FIFO is enabled, the RXFE bit is set
             * when the receive FIFO is empty.
             *
             * Type: RO
             * Reset: 0x1
             */
            uint32_t RXFE : 1;
            /* Transmit FIFO full. The meaning of this bit depends on the
             * state of the FEN bit in the UARTLCR_H Register. If the
             * FIFO is disabled, this bit is set when the transmit holding
             * register is full. If the FIFO is enabled, the TXFF bit is set
             * when the transmit FIFO is full.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t TXFF : 1;
            /* Receive FIFO full. The meaning of this bit depends on the
             * state of the FEN bit in the UARTLCR_H Register. If the
             * FIFO is disabled, this bit is set when the receive holding
             * register is full. If the FIFO is enabled, the RXFF bit is set
             * when the receive FIFO is full.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t RXFF : 1;
            /* Transmit FIFO empty. The meaning of this bit depends on
             * the state of the FEN bit in the Line Control Register,
             * UARTLCR_H. If the FIFO is disabled, this bit is set when
             * the transmit holding register is empty. If the FIFO is
             * enabled, the TXFE bit is set when the transmit FIFO is
             * empty. This bit does not indicate if there is data in the
             * transmit shift register.
             *
             * Type: RO
             * Reset: 0x1
             */
            uint32_t TXFE : 1;
            /* Ring indicator. This bit is the complement of the UART
             * ring indicator, nUARTRI, modem status input. That is, the
             * bit is 1 when nUARTRI is LOW.
             *
             * Type: RO
             */
            uint32_t RI : 1;
            uint32_t : 23;
        };
        /* All register bits. */
        uint32_t all;
    } UARTFR;

    uint32_t : 32;

    /* IrDA Low-Power Counter Register. */
    union
    {
        struct
        {
            /* 8-bit low-power divisor value. These bits are cleared to 0 at reset.
             *
             * Type: RW
             * Rest: 0x00
             */
            uint32_t ILPDVSR : 8;
            uint32_t : 24;
        };
        uint32_t all;
    } UARTILPR;

    /* Integer Baud Rate Register. */
    union
    {
        struct
        {
            /* The integer baud rate divisor. These bits are cleared to 0 at reset.
             *
             * Type: RW
             * Rest: 0x0000
             */
            uint32_t BAUD_DIVINT : 16;
            uint32_t : 16;
        };
        uint32_t all;
    } UARTIBRD;

    /* Fractional Baud Rate Register. */
    union
    {
        struct
        {
            /* The fractional baud rate divisor. These bits are cleared to 0 at reset.
             *
             * Type: RW
             * Rest: 0x00
             */
            uint32_t BAUD_DIVFRAC : 6;
            uint32_t : 26;
        };
        uint32_t all;
    } UARTFBRD;

    /* Line Control Register. */
    union
    {
        struct
        {
            /* Send break. If this bit is set to 1, a low-level is continually
             * output on the UARTTXD output, after completing
             * transmission of the current character. For the proper
             * execution of the break command, the software must set
             * this bit for at least two complete frames. For normal use,
             * this bit must be cleared to 0.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t BRK : 1;
            /* Parity enable: 0 = parity is disabled and no parity bit added
             * to the data frame 1 = parity checking and generation is enabled.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t PEN : 1;
            /* Even parity select. Controls the type of parity the UART
             * uses during transmission and reception: 0 = odd parity.
             * The UART generates or checks for an odd number of 1s in
             * the data and parity bits. 1 = even parity. The UART
             * generates or checks for an even number of 1s in the data
             * and parity bits. This bit has no effect when the PEN bit
             * disables parity checking and generation.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t EPS : 1;
            /* Two stop bits select. If this bit is set to 1, two stop bits are
             * transmitted at the end of the frame. The receive logic
             * does not check for two stop bits being received.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t STP2 : 1;
            /* Enable FIFOs: 0 = FIFOs are disabled (character mode)
             * that is, the FIFOs become 1-byte-deep holding registers 1
             * = transmit and receive FIFO buffers are enabled (FIFO
             * mode).
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t FEN : 1;
            /* Word length. These bits indicate the number of data bits
             * transmitted or received in a frame as follows:
             * b11 = 8 bits
             * b10 = 7 bits
             * b01 = 6 bits
             * b00 = 5 bits
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t WLEN : 2;
            /* Stick parity select. 0 = stick parity is disabled 1 = either: *
             * if the EPS bit is 0 then the parity bit is transmitted and
             * checked as a 1 * if the EPS bit is 1 then the parity bit is
             * transmitted and checked as a 0. This bit has no effect
             * when the PEN bit disables parity checking and generation.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t SPS : 1;
            uint32_t : 24;
        };
        uint32_t all;
    } UARTLCR_H;

    /* Control Register. */
    union
    {
        struct
        {
            /* UART enable: 0 = UART is disabled. If the UART is disabled
             * in the middle of transmission or reception, it completes
             * the current character before stopping. 1 = the UART is
             * enabled. Data transmission and reception occurs for
             * either UART signals or SIR signals depending on the
             * setting of the SIREN bit.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t UARTEN : 1;
            /* SIR enable: 0 = IrDA SIR ENDEC is disabled. nSIROUT
             * remains LOW (no light pulse generated), and signal
             * transitions on SIRIN have no effect. 1 = IrDA SIR ENDEC is
             * enabled. Data is transmitted and received on nSIROUT and
             * SIRIN. UARTTXD remains HIGH, in the marking state.
             * Signal transitions on UARTRXD or modem status inputs
             * have no effect. This bit has no effect if the UARTEN bit
             * disables the UART.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t SIREN : 1;
            /* SIR low-power IrDA mode. This bit selects the IrDA
             * encoding mode. If this bit is cleared to 0, low-level bits are
             * transmitted as an active high pulse with a width of 3 /
             * 16th of the bit period. If this bit is set to 1, low-level bits
             * are transmitted with a pulse width that is 3 times the
             * period of the IrLPBaud16 input signal, regardless of the
             * selected bit rate. Setting this bit uses less power, but
             * might reduce transmission distances.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t SIRLP : 1;
            uint32_t : 4;
            /* Loopback enable. If this bit is set to 1 and the SIREN bit is
             * set to 1 and the SIRTEST bit in the Test Control Register,
             * UARTTCR is set to 1, then the nSIROUT path is inverted,
             * and fed through to the SIRIN path. The SIRTEST bit in the
             * test register must be set to 1 to override the normal half-
             * duplex SIR operation. This must be the requirement for
             * accessing the test registers during normal operation, and
             * SIRTEST must be cleared to 0 when loopback testing is
             * finished. This feature reduces the amount of external
             * coupling required during system test. If this bit is set to 1,
             * and the SIRTEST bit is set to 0, the UARTTXD path is fed
             * through to the UARTRXD path. In either SIR mode or UART
             * mode, when this bit is set, the modem outputs are also fed
             * through to the modem inputs. This bit is cleared to 0 on
             * reset, to disable loopback.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t LBE : 1;
            /* Transmit enable. If this bit is set to 1, the transmit section
             * of the UART is enabled. Data transmission occurs for
             * either UART signals, or SIR signals depending on the
             * setting of the SIREN bit. When the UART is disabled in the
             * middle of transmission, it completes the current character
             * before stopping.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t TXE : 1;
            /* Receive enable. If this bit is set to 1, the receive section of
             * the UART is enabled. Data reception occurs for either
             * UART signals or SIR signals depending on the setting of
             * the SIREN bit. When the UART is disabled in the middle of
             * reception, it completes the current character before
             * stopping.
             *
             * Type: RW
             * Reset: 0x1
             */
            uint32_t RXE : 1;
            /* Data transmit ready. This bit is the complement of the
             * UART data transmit ready, nUARTDTR, modem status
             * output. That is, when the bit is programmed to a 1 then
             * nUARTDTR is LOW.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t DTR : 1;
            /* Request to send. This bit is the complement of the UART
             * request to send, nUARTRTS, modem status output. That
             * is, when the bit is programmed to a 1 then nUARTRTS is
             * LOW.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RTS : 1;
            /* This bit is the complement of the UART Out1 (nUARTOut1)
             * modem status output. That is, when the bit is
             * programmed to a 1 the output is 0. For DTE this can be
             * used as Data Carrier Detect (DCD).
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t OUT1 : 1;
            /* This bit is the complement of the UART Out2 (nUARTOut2)
             * modem status output. That is, when the bit is
             * programmed to a 1, the output is 0. For DTE this can be
             * used as Ring Indicator (RI).
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t OUT2 : 1;
            /* RTS hardware flow control enable. If this bit is set to 1,
             * RTS hardware flow control is enabled. Data is only
             * requested when there is space in the receive FIFO for it to
             * be received.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RTSEN : 1;
            /* CTS hardware flow control enable. If this bit is set to 1,
             * CTS hardware flow control is enabled. Data is only
             * transmitted when the nUARTCTS signal is asserted.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t CTSEN : 1;
            uint32_t : 16;
        };
        uint32_t all;
    } UARTCR;

    /* Interrupt FIFO Level Select Register. */
    union
    {
        struct
        {
            /* Transmit interrupt FIFO level select. The trigger points for
             * the transmit interrupt are as follows:
             * b000 = Transmit FIFO becomes <= 1 / 8 full
             * b001 = Transmit FIFO becomes <= 1 / 4 full
             * b010 = Transmit FIFO becomes <= 1 / 2 full
             * b011 = Transmit FIFO becomes <= 3 / 4 full
             * b100 = Transmit FIFO becomes <= 7 / 8 full
             * b101-b111 = reserved
             *
             * Type: RW
             * Reset: 0x2
             */
            uint32_t TXIFLSEL : 3;
            /* Receive interrupt FIFO level select. The trigger points for
             * the receive interrupt are as follows:
             * b000 = Receive FIFO becomes >= 1 / 8 full
             * b001 = Receive FIFO becomes >= 1 / 4 full
             * b010 = Receive FIFO becomes >= 1 / 2 full
             * b011 = Receive FIFO becomes >= 3 / 4 full
             * b100 = Receive FIFO becomes >= 7 / 8 full
             * b101-b111 = reserved
             *
             * Type: RW
             * Reset: 0x2
             */
            uint32_t RXIFLSEL : 3;
            uint32_t : 26;
        };
        uint32_t all;
    } UARTIFLS;

    /* Interrupt Mask Set/Clear Register. */
    union
    {
        struct
        {
            /* nUARTRI modem interrupt mask. A read returns the
             * current mask for the UARTRIINTR interrupt. On a write of
             * 1, the mask of the UARTRIINTR interrupt is set. A write of
             * 0 clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RIMIM : 1;
            /* nUARTCTS modem interrupt mask. A read returns the
             * current mask for the UARTCTSINTR interrupt. On a write
             * of 1, the mask of the UARTCTSINTR interrupt is set. A
             * write of 0 clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t CTSMIM : 1;
            /* nUARTDCD modem interrupt mask. A read returns the
             * current mask for the UARTDCDINTR interrupt. On a write
             * of 1, the mask of the UARTDCDINTR interrupt is set. A
             * write of 0 clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t DCDMIM : 1;
            /* nUARTDSR modem interrupt mask. A read returns the
             * current mask for the UARTDSRINTR interrupt. On a write
             * of 1, the mask of the UARTDSRINTR interrupt is set. A
             * write of 0 clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t DSRMIM : 1;
            /* Receive interrupt mask. A read returns the current maskRW0x0
             * for the UARTRXINTR interrupt. On a write of 1, the mask of
             * the UARTRXINTR interrupt is set. A write of 0 clears the
             * mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RXIM : 1;
            /* Transmit interrupt mask. A read returns the current mask
             * for the UARTTXINTR interrupt. On a write of 1, the mask of
             * the UARTTXINTR interrupt is set. A write of 0 clears the
             * mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t TXIM : 1;
            /* Receive timeout interrupt mask. A read returns the current
             * mask for the UARTRTINTR interrupt. On a write of 1, the
             * mask of the UARTRTINTR interrupt is set. A write of 0
             * clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RTIM : 1;
            /* Framing error interrupt mask. A read returns the current
             * mask for the UARTFEINTR interrupt. On a write of 1, the
             * mask of the UARTFEINTR interrupt is set. A write of 0
             * clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t FEIM : 1;
            /* Parity error interrupt mask. A read returns the current
             * mask for the UARTPEINTR interrupt. On a write of 1, the
             * mask of the UARTPEINTR interrupt is set. A write of 0
             * clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t PEIM : 1;
            /* Break error interrupt mask. A read returns the current
             * mask for the UARTBEINTR interrupt. On a write of 1, the
             * mask of the UARTBEINTR interrupt is set. A write of 0
             * clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t BEIM : 1;
            /* Overrun error interrupt mask. A read returns the current
             * mask for the UARTOEINTR interrupt. On a write of 1, the
             * mask of the UARTOEINTR interrupt is set. A write of 0
             * clears the mask.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t OEIM : 1;
            uint32_t : 21;
        };
        uint32_t all;
    } UARTIMSC;

    /* Raw Interrupt Status Register. */
    union
    {
        struct
        {
            /* nUARTRI modem interrupt status. Returns the raw
             * interrupt state of the UARTRIINTR interrupt.
             *
             * Type: RO
             */
            uint32_t RIRMIS : 1;
            /* nUARTCTS modem interrupt status. Returns the raw
             * interrupt state of the UARTCTSINTR interrupt.
             *
             * Type: RO
             */
            uint32_t CTSRMIS : 1;
            /* nUARTDCD modem interrupt status. Returns the raw
             * interrupt state of the UARTDCDINTR interrupt.
             *
             * Type: RO
             */
            uint32_t DCDRMIS : 1;
            /* nUARTDSR modem interrupt status. Returns the raw
             * interrupt state of the UARTDSRINTR interrupt.
             *
             * Type: RO
             */
            uint32_t DSRRMIS : 1;
            /* Receive interrupt status. Returns the raw interrupt state of
             * the UARTRXINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t RXRIS : 1;
            /* Transmit interrupt status. Returns the raw interrupt state of
             * the UARTTXINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t TXRIS : 1;
            /* Receive timeout interrupt status. Returns the raw interrupt state of
             * the UARTRTINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t RTRIS : 1;
            /* Framing error interrupt status. Returns the raw interrupt state of
             * the UARTFEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t FERIS : 1;
            /* Parity error interrupt status. Returns the raw interrupt state of
             * the UARTPEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t PERIS : 1;
            /* Break error interrupt status. Returns the raw interrupt state of
             * the UARTBEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t BERIS : 1;
            /* Overrun error interrupt status. Returns the raw interrupt state of
             * the UARTOEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t OERIS : 1;
            uint32_t : 21;
        };
        uint32_t all;
    } UARTRIS;

    /* Masked Interrupt Status Register. */
    union
    {
        struct
        {
            /* nUARTRI modem masked interrupt status. Returns the masked
             * interrupt state of the UARTRIINTR interrupt.
             *
             * Type: RO
             */
            uint32_t RIMMIS : 1;
            /* nUARTCTS modem masked interrupt status. Returns the masked
             * interrupt state of the UARTCTSINTR interrupt.
             *
             * Type: RO
             */
            uint32_t CTSMMIS : 1;
            /* nUARTDCD modem masked interrupt status. Returns the masked
             * interrupt state of the UARTDCDINTR interrupt.
             *
             * Type: RO
             */
            uint32_t DCDMMIS : 1;
            /* nUARTDSR modem masked interrupt status. Returns the masked
             * interrupt state of the UARTDSRINTR interrupt.
             *
             * Type: RO
             */
            uint32_t DSRMMIS : 1;
            /* Receive masked interrupt status. Returns the masked interrupt state of
             * the UARTRXINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t RXMIS : 1;
            /* Transmit masked interrupt status. Returns the masked interrupt state of
             * the UARTTXINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t TXMIS : 1;
            /* Receive timeout masked interrupt status. Returns the masked interrupt state of
             * the UARTRTINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t RTMIS : 1;
            /* Framing error masked interrupt status. Returns the masked interrupt state of
             * the UARTFEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t FEMIS : 1;
            /* Parity error masked interrupt status. Returns the masked interrupt state of
             * the UARTPEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t PEMIS : 1;
            /* Break error masked interrupt status. Returns the masked interrupt state of
             * the UARTBEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t BEMIS : 1;
            /* Overrun error masked interrupt status. Returns the masked interrupt state of
             * the UARTOEINTR interrupt.
             *
             * Type: RO
             * Reset: 0x0
             */
            uint32_t OEMIS : 1;
            uint32_t : 21;
        };
        uint32_t all;
    } UARTMIS;

    /* Interrupt Clear Register. */
    union
    {
        struct
        {
            /* nUARTRI modem interrupt clear. Clears the UARTRIINTR interrupt.
             *
             * Type: WC
             */
            uint32_t RIMIC : 1;
            /* nUARTCTS modem interrupt clear. Clears the UARTCTSINTR interrupt.
             *
             * Type: WC
             */
            uint32_t CTSMIC : 1;
            /* nUARTDCD modem interrupt clear. Clears the UARTDCDINTR interrupt.
             *
             * Type: WC
             */
            uint32_t DCDMIC : 1;
            /* nUARTDSR modem interrupt clear. Clears the UARTDSRINTR interrupt.
             *
             * Type: WC
             */
            uint32_t DSRMIC : 1;
            /* Receive interrupt clear. Clears the UARTRXINTR interrupt.
             *
             * Type: WC
             */
            uint32_t RXIC : 1;
            /* Transmit interrupt clear. Clears the UARTTXINTR interrupt.
             *
             * Type: WC
             */
            uint32_t TXIC : 1;
            /* Receive timeout interrupt clear. Clears the UARTRTINTR interrupt.
             *
             * Type: WC
             */
            uint32_t RTIC : 1;
            /* Framing error interrupt clear. Clears the UARTFEINTR interrupt.
             *
             * Type: WC
             */
            uint32_t FEIC : 1;
            /* Parity error interrupt clear. Clears the UARTPEINTR interrupt.
             *
             * Type: WC
             */
            uint32_t PEIC : 1;
            /* Break error interrupt clear. Clears the UARTBEINTR interrupt.
             *
             * Type: WC
             */
            uint32_t BEIC : 1;
            /* Overrun error interrupt clear. Clears the UARTOEINTR interrupt.
             *
             * Type: WC
             */
            uint32_t OEIC : 1;
            uint32_t : 21;
        };
        uint32_t all;
    } UARTICR;

    /* DMA Control Register. */
    union
    {
        struct
        {
            /* Receive DMA enable. If this bit is set to 1, DMA for the
             * receive FIFO is enabled.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t RXDMAE : 1;
            /* Transmit DMA enable. If this bit is set to 1, DMA for the
             * transmit FIFO is enabled.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t TXDMAE : 1;
            /* DMA on error. If this bit is set to 1, the DMA receive
             * request outputs, UARTRXDMASREQ or UARTRXDMABREQ,
             * are disabled when the UART error interrupt is asserted.
             *
             * Type: RW
             * Reset: 0x0
             */
            uint32_t DMAONERR : 1;
            uint32_t : 21;
        };
        uint32_t all;
    } UARTDMACR;
} UART_registers_t;

extern volatile UART_registers_t UART0;
extern volatile UART_registers_t UART1;
