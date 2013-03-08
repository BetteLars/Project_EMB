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
/***************************** Include files *******************************/
//stallaris includes
#include <string.h>
#include <stdio.h>

#include "inc/hw_memmap.h"

#include "inc/lm3s9b92.h"

//include
#include "hardware_init.h"
#include "initCANprog.h"
#include "inc/vcp.h"
#include "inc/emp_type.h"
#include "button.h"
#include "statemashine.h"
#include "inc/swtimers.h"
//!Globel variables
//! Set key events to no event so it not "flooting"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
volatile INT16S ticks = 0;

INT16S alive_timer = TIM_500_MSEC;
INT16S task_timer  = TIM_1_SEC;


/*****************************   Functions   *******************************/
//! Function prototypes
void SimpleDelay()
{
	INT16U delaytimer;
    //
    // Delay cycles for 1 second
    //
    for(delaytimer = 0; delaytimer<20000; delaytimer++);
}

//! With this setup it would seem like main() must be the first function in this file, otherwise
//! the wrong function gets called on reset.
//!Setting up the Display

void main(void)
 {
	volatile INT32U ulLoop;

	volatile INT16U push;
	//Hardware upstarts


		disable_global_int();
		init_clk_system();
		initHW();
		init_systick();
		init_UART(UART0_BASE, 115200);
		Init_CAN();
		enable_global_int();


	//! Start the OLED display and write a message on it

    // Clean the OLED display.

	//
	// Loop forever.
	//
	while (1)
	{
		  // System part of the super loop.
		  // ------------------------------
		  while( !ticks );

		  // The following will be executed every 10mS
		  ticks--;
		  if( ! --alive_timer )
		  {
	      alive_timer =	TIM_500_MSEC;
		    GPIO_PORTF_DATA_R ^= 0x01;
		  }
		    // Protected operating system mode

		// Statmashine function
		// This is where a statemachine could be added

		push = select_button();
		statemashine(push);
		//all functions the
		//UARTprintf("ucData: 0x%02X %02X %02X %02X %02X %02X %02X %02X",ucDataOut[0], ucDataOut[1], ucDataOut[2], ucDataOut[3],ucDataOut[4], ucDataOut[5], ucDataOut[6], ucDataOut[7]);

	}

}
