/*
 * readkeys.h
 *
 *  Created on: 2012
 *      Author: Lars
 */
/*
 ============================================================================
 Name        : Motor
 Author      : Lars
 Version     :
 Copyright   : Your copyright notice
 Description : H_bridge control in C, Ansi-style
 ============================================================================
 */
//stallaris includes
#include <string.h>
#include <stdio.h>

#include "inc/lm3s6965.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//include
#include "drivers/rit128x96x4.h"
#include "drivers/F_PWM.h"
#include "drivers/setADC.h"
#include "inc/emp_type.h"
#include "readkeys/readkeys.h"
#include "statemashine.h"
#include "button.h"
//!Setting up the Display
#define mainCHARACTER_HEIGHT				( 9 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 	)
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )

//! Function prototypes
void initHW(void);

//!Globel variables
int event = NO_EVENT;//! Set key events to no event so it not "flooting"


void SimpleDelay(time)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / time);
}
//! With this setup it would seem like main() must be the first function in this file, otherwise
//! the wrong function gets called on reset.
void main(void)
 {
	volatile INT32U ulLoop;
	volatile INT16U event;
	volatile INT16U push;
	//Hardware upstarts
	initHW();

	//! Start the OLED display and write a message on it
	RIT128x96x4Init(ulSSI_FREQUENCY);
	RIT128x96x4StringDraw("EMP", 					15, 42, mainFULL_SCALE);
	RIT128x96x4StringDraw("enter the code.....",	 5, 49, mainFULL_SCALE);
	RIT128x96x4StringDraw("SW2 SW3 SW4 SW5 SW6", 		15, 57, mainFULL_SCALE);
	// Entry Password see under inputs
	// Wait for the select key to be pressed
	while (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
	// Wait for the select key to be pressed
	while (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_0));
	// Wait for the select key to be pressed
	while (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1));
	// Wait for the select key to be pressed
	while (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2));
	// Wait for the select key to be pressed
	while (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3));

    // Clean the OLED display.
	RIT128x96x4Clear();
	//
	// Loop forever.
	//
	while (1)
	{

		// Statmashine function
		// This is where a statemachine could be added
		event = GetKeyEvents();
		  push = select_button();
		statemashine(event , push);
		//all functions the

	}

}

void initHW(void)
{
	volatile INT16U event;
	volatile INT32U ulLoop;
	//SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);//set to use osc its better for pwm
	//! Enable the ports
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	// Inputs :
	// PF1 : Select button
	// PE0 : Up button
	// PE1 : Down button
	// PE2 : Left button
	// PE3 : Right button
	GPIODirModeSet(		GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(	GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIODirModeSet(		GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(	GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	// Outputs:
		// PF0 : Status LED
	GPIODirModeSet(		GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT);
	GPIOPadConfigSet(	GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	GPIOPinWrite(		GPIO_PORTF_BASE, GPIO_PIN_0, false);
		//! PD6 : LED1 RED
	 // Set the direction as output (PF0).
	GPIO_PORTD_DIR_R = 0x40;
	// Enable the GPIO pins for digital function (PF0 and PF1).
	GPIO_PORTD_DEN_R = 0x40;
		//! PG0 : LED2 YELLOW
		//! PG1 : LED3 GREEN
	GPIO_PORTG_DIR_R = 0x03;
	// Enable the GPIO pins for digital function (PF0 and PF1).
	GPIO_PORTG_DEN_R = 0x03;

	//off
		//! PD6 : LED1 RED
	GPIO_PORTD_DATA_R |= 0x40;
		//! PG0+PG1 : LED2 YELLOW + LED3 GREEN
	GPIO_PORTG_DATA_R |= 0x03;

	// a short delay to ensure stable IO before running the rest of the program
	SimpleDelay(5);
}
