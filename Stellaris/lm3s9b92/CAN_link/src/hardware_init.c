/*
 * hardware_init.c
 *
 *  Created on: 27/02/2013
 *      Author: Lasse
 */
/***************************** Include files *******************************/
#include <string.h>
#include <stdio.h>
#include "C:/StellarisWare/inc/lm3s9b92.h"
#include "inc/emp_type.h"

#include "inc/hw_memmap.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void initHW(void)
{
	volatile INT16U event;
	volatile INT32U ulLoop;
	volatile INT8S dummy;
	// Enable the GPIO port that is used for the on-board.
		SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOD;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
		dummy = SYSCTL_RCGC2_R;

	// Outputs:
	// Set the direction as output (PD0).
		// PD0		: Status LED intern USR_LED
		GPIO_PORTD_DIR_R = 0x01;

	// inputs :
	// Enable internal pull-up (PB4).
		// PB4				: Select button SW2
		GPIO_PORTB_PUR_R = 0x08;

	// Enable the GPIO pins for digital function (PD6, PF0, PF1, PG0 and PG1).
		// PD0  +PB4		: intern USR_LED + SW2
		GPIO_PORTB_DEN_R = 0x08;
		GPIO_PORTD_DEN_R = 0x01;
	// a short delay to ensure stable IO before running the rest of the program
	SimpleDelay();

}
void init_clk_system(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function :
*****************************************************************************/
{
	// Init clock settings according to datasheet
	// Set Clock speed to 50 Mhz.

	// Step 1
	// Set BYPASS bit
	SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;
	// Clear USESYS bits
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_USESYSDIV);
	// Enable Main osc.
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_MOSCDIS);

	// Step 2
	// Clear PLL lock flag
	//SYSCTL_RIS_R = ~(SYSCTL_RIS_PLLLRIS);
	SYSCTL_MISC_R |= SYSCTL_RIS_PLLLRIS;

	// Set XTAL value, first clear bits then set
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_XTAL_M);
	SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;
	// delay
	SimpleDelay();
	// Set OSCSRC, first clear bits then set
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_OSCSRC_M);
	SYSCTL_RCC_R |= SYSCTL_RCC_OSCSRC_MAIN;
	// Clear PWRDN
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_PWRDN);

	// delay
	SimpleDelay();

	// Step 3
	// Set SYSDIV, first clear bits then set
	// Set to 50 Mhz.
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_SYSDIV_M);
	SYSCTL_RCC_R |= SYSCTL_RCC_SYSDIV_4;
	// Set USESYS bit
	SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;

	// Step 4
	// wait for PLL lock
	while(!(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS));

	// Step 5
	// Clear BYPASS bit
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_BYPASS);

	// delay
	SimpleDelay();
}
void enable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	// enable interrupts.
	asm(" cpsie i");
}

void disable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // disable interrupts.
  asm(" cpsid i");
}
/****************************** End Of Module *******************************/

