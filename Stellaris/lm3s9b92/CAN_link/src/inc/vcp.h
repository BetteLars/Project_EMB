/*
========================================================================================
 Name        : vcp.h
 Author      : Lasse Nielsen and Martin Valentinsen
 Created on  : 25/01/2013
 Version     :
 Copyright   : Copyright (C)
 Description : Virtual Com Port. Everything regarding the UART on VCP.
========================================================================================
*/
#ifndef VCP_H_
#define VCP_H_

#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine);
#endif

#define HWREG(x)    			(*((volatile unsigned long *)(x)))

//Configuration for uart:for no parity, 1 stop bit and w length 8.
//See LCRH register for info
#define UART_CONFIG 			0x60

//Interrupts
#define INT_UART0               21          // UART0 Rx and Tx
#define INT_UART1               22          // UART1 Rx and Tx
#define INT_UART2               49          // UART2 Rx and Tx
//*****************************************************************************
//
// Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
// as the ulIntFlags parameter, and returned from UARTIntStatus.
//
//*****************************************************************************
#define UART_INT_OE             0x400       // Overrun Error Interrupt Mask
#define UART_INT_BE             0x200       // Break Error Interrupt Mask
#define UART_INT_PE             0x100       // Parity Error Interrupt Mask
#define UART_INT_FE             0x080       // Framing Error Interrupt Mask
#define UART_INT_RT             0x040       // Receive Timeout Interrupt Mask
#define UART_INT_TX             0x020       // Transmit Interrupt Mask
#define UART_INT_RX             0x010       // Receive Interrupt Mask
#define UART_INT_DSR            0x008       // DSR Modem Interrupt Mask
#define UART_INT_DCD            0x004       // DCD Modem Interrupt Mask
#define UART_INT_CTS            0x002       // CTS Modem Interrupt Mask
#define UART_INT_RI             0x001       // RI Modem Interrupt Mask

#define UART_TXINT_MODE_FIFO    0x00000000
#define UART_TXINT_MODE_EOT     0x00000010

void init_UART(unsigned long ulBase, unsigned long ulBaud);
void UARTSend(unsigned long ulBase, const unsigned char *pucBuffer, unsigned long ulCount);
void UARTRecieve(unsigned long ulBase, unsigned char* str);

#endif /* VCP_H_ */
