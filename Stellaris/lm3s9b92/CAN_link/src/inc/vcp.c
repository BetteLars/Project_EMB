/*
========================================================================================
 Name        : vcp.c
 Author      : Lasse Nielsen and Martin Valentinsen
 Created on  : 25/01/2013
 Version     :
 Copyright   : Copyright (C)
 Description : Virtual Com Port. Everything regarding the UART on VCP.
========================================================================================
*/

#include "hw_memmap.h"
#include "hw_uart.h"
#include "lm3s9b92.h"
#include "../statemashine.h"
#include "vcp.h"
#include <string.h>
#include <stdio.h>

#define FCPU					50000000

void
__error__(char *pcFilename, unsigned long ulLine)
{
}
void SetBaudRate(unsigned long ulBase, unsigned long ulBaud){
	unsigned long ulDiv, ulUARTClk = FCPU;

	//********* First disable uart ***************
	// Wait for end of TX.
    while(HWREG(ulBase + UART_O_FR) & UART_FR_BUSY)
    {
    }
    // Disable the FIFO.
    HWREG(ulBase + UART_O_LCRH) &= ~(UART_LCRH_FEN);
    // Disable the UART.
    HWREG(ulBase + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);
    //*********************************************
    //**************** Set BaudRate ***************
    // Is the required baud rate greater than the maximum rate supported
    // without the use of high speed mode?
    if((ulBaud * 16) > ulUARTClk)
    {
        // Enable high speed mode.
        HWREG(ulBase + UART_O_CTL) |= UART_CTL_HSE;
        // Half the supplied baud rate to compensate for enabling high speed
        // mode.  This allows the following code to be common to both cases.
        ulBaud /= 2;
    } else
    {
        // Disable high speed mode.
        HWREG(ulBase + UART_O_CTL) &= ~(UART_CTL_HSE);
    }
    // Compute the fractional baud rate divider.
    ulDiv = (((ulUARTClk * 8) / ulBaud) + 1) / 2;
    // Set the baud rate.
    HWREG(ulBase + UART_O_IBRD) = ulDiv / 64;
    HWREG(ulBase + UART_O_FBRD) = ulDiv % 64;
    //*********************************************

    //Setup for no parity, 1 stop bit and w length 8. And clear flags
    HWREG(ulBase + UART_O_LCRH) = UART_CONFIG;
    HWREG(ulBase + UART_O_FR) = 0;

    //******** Enable uart again ******************
    // Enable the FIFO.
    HWREG(ulBase + UART_O_LCRH) |= UART_LCRH_FEN;
    // Enable RX, TX, and the UART.
    HWREG(ulBase + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);
    //*********************************************
}

void init_UART(unsigned long ulBase, unsigned long ulBaud){
	unsigned long interrup;
	switch(ulBase){
	case UART0_BASE:
		// Enable the peripherals for UART0.
		SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

		// Set GPIO A0 and A1 as UART pins. Side 412 viser eksempel
		GPIO_PORTA_AFSEL_R |= 0x03; // 1 for "alternate function"
		GPIO_PORTA_DEN_R |= 0x03;
		// Everything else is set to default
		interrup = 1 << (INT_UART0 - 16);
		break;
	case UART1_BASE:
		break;
	case UART2_BASE:
		break;
	default:
		return;
	}

	//Configure UART
	SetBaudRate(ulBase,ulBaud);

    // Enable the UART interrupt.
	NVIC_EN0_R |= interrup;
	HWREG(ulBase + UART_O_IM) |= UART_INT_RX | UART_INT_RT;// | UART_INT_TX
	//Set Tx interrupt til eot, dvs når bufferen er helt tom.
	HWREG(ulBase + UART_O_CTL) |= UART_TXINT_MODE_EOT;
	//Init interrupt semaphores
    //UARTIntSem = init_semaphore("UARTRx");
   //UARTTxSem = init_semaphore("UARTTx");
}

//*****************************************************************************
//
// The UART interrupt handler.
//! \addgroup UART_int_handler
//! @{
//*****************************************************************************
void UART0IntHandler(void)
{
	unsigned long ulBase = UART0_BASE;
    unsigned long ulStatus;

    // Get the masked interrrupt status.
    ulStatus = HWREG(ulBase + UART_O_MIS);

    // Clear the asserted interrupts.
    HWREG(ulBase + UART_O_ICR) = ulStatus;

    // If interrupt is RX or RT.. signal the recieve sem
    // The TX-semaphore is only signaled if someone is waiting for the fifo to empty
    /*
    if (ulStatus & (UART_IM_RTIM | UART_IM_RXIM))
    	signal_semaphore(UARTIntSem);
    else if (ulStatus & UART_IM_TXIM && UARTTxSem->pending)
    	signal_semaphore(UARTTxSem);
     */
    if (ulStatus & (UART_IM_RTIM | UART_IM_RXIM))
    {
    	UARTRecieve(UART0_BASE,buffer);
    }

}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
void UARTSend(unsigned long ulBase, const unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Loop while there are more characters to send.
    //
    while(ulCount-- && *pucBuffer != '\0')
    {
        //
        // Write the next character to the UART.
        //
    	/*
        if(HWREG(ulBase + UART_O_FR) & UART_FR_TXFF)
        {
        	wait_semaphore(UARTTxSem,NO_TIMEOUT);
        }
        */
        while(HWREG(ulBase + UART_O_FR) & UART_FR_TXFF)
        {

        }
        HWREG(ulBase + UART_O_DR) = *pucBuffer++;
    }
}

void UARTRecieve(unsigned long ulBase, unsigned char* str){
    long i = 0;
    int j = 0;
    while(!(HWREG(ulBase + UART_O_FR) & UART_FR_RXFE)) {
    	i = HWREG(ulBase + UART_O_DR);
    	str[j] = (unsigned char)i;
    	j++;
    }
}
