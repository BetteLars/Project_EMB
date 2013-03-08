/*
 * Example code for a very simple statemachine.
 *
 * Used in teaching C programming on embedded systems at EAL with modyfaksion from Lars
 *
 */
/*
 ============================================================================
 Name        : Statemashine.c
 Author      : Lars
 Version     :
 Copyright   : Your copyright notice
 Description : Statemashine to motor and LED outputs in C, Ansi-style
 ============================================================================
 */
//*****************************************************************************
//
//! \addtogroup StateMashine
//! @{
//
//*****************************************************************************
/***************************** Include files *******************************/
#include "inc/lm3s6965.h"
#include "inc/emp_type.h"

#include "inc/itoa.h"

#include "statemashine.h"

#include "events.h"
#include "CAN_defines.h"



//! State definitions
//! this is where to set where in the Menu its starts up when you power up the statemashine
INT16U TS_State = CAN_menu;



/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
INT8U buffer[32];

/*****************************   Functions   *******************************/
/* The SM does not know anything about the system. This way it can be tested on a
 * different C compiler very easily.
 */
int statemashine(int press )
{
	INT16U next_state = TS_State;

	//!there is 5 buttons to use in this statemashine its @param KEY?_EVENT_?
	//! and under them is what happen if you push it... every case end on break;
	switch( TS_State )
    {
	case IGNITION:
		break;
	default:
		break;
	// The program should never get here !
    }

    if (next_state != TS_State)	//! is set want the state mashine do after it round one time ture the program after a state is changed
    {
    	OnExit(TS_State);		//! befor it changes
		OnEnter(next_state);		//! after it changes
        TS_State = next_state;
    }


    DoDisplay( TS_State, press);//!what the state mashine every time it run ture the program

return TS_State;
}

/* The 3 functions OnEnter, OnExit and Do are were all the fun happens.
 * Theee functions are written specifically for this system, and must be replaced
 * if the SM is used somewhere else - say on an embedded system.
 *
 * For simulating the SM a bunch of statements should be put here.
 */

void OnEnter( State)
{
// /n
}

void OnExit( State)
{

}

void DoDisplay( State, button)
{
	switch(State)// to show menu display at start i set it here
		{
		case CAN_menu:
			break;
		default:
			break;
			// The program should never get here
		}

	switch (button)//!to see want button is pressed in all menus they are set here(debug)
		{
		case BE_SINGLE_PUSH:
			UARTSend(UART0_BASE,"  single push  ",15);
			break;

		case BE_DOUBBLE_PUSH:
			UARTSend(UART0_BASE,"  Doubble push ",15);
			break;

		case BE_LONG_PUSH:
			UARTSend(UART0_BASE,"   long push   ",15);
			break;
		default:
			break;
		}
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
