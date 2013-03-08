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
//Includes
#include "inc/lm3s6965.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/emp_type.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "drivers/rit128x96x4.h"
#include "externalFunctions/itoa.h"
#include "readkeys/readkeys.h"
#include "statemashine.h"
#include "binarycounter.h"
#include "button.h"
#include "events.h"
//Defines
#define mainCHARACTER_HEIGHT				( 9 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 	)
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )

//! State definitions
//! this is where to set where in the Menu its starts up when you power up the statemashine

INT16U TS_State = UPSTARTMENU;

char buffer[32];
/* The SM does not know anything about the system. This way it can be tested on a
 * different C compiler very easily.
 */
int statemashine( int event, int press )
{
	INT16U next_state = TS_State;
    static INT8S num = 0;
    static INT16U counter_timer = 0;
	//!there is 5 buttons to use in this statemashine its @param KEY?_EVENT_?
	//! and under them is what happen if you push it... every case end on break;
	switch( TS_State )
    {
	case UPSTARTMENU:
		switch (event)
		{
		case KEY0_EVENT_SELECT:
			break;

		case KEY1_EVENT_UP:
			next_state = upMANUELLED;
			break;

		case KEY2_EVENT_DOWN:
			next_state = downMANUELLED;
			break;

		case KEY3_EVENT_ENTER:
			next_state = LED;
			break;

		case KEY4_EVENT_CANCEL:
			break;
		default:
			break;
		}
		break;

	case LED:
		switch (event)
		{
		case KEY0_EVENT_SELECT:
			next_state = UPSTARTMENU;
			break;

		case KEY1_EVENT_UP:
			//!turn on led on the board
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
			RIT128x96x4StringDraw("LED ON  ",				2,	77, mainFULL_SCALE);
			break;

		case KEY2_EVENT_DOWN:
			//!turn on led off the board
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
			RIT128x96x4StringDraw("LED OFF ",				2,	77, mainFULL_SCALE);
			break;

		case KEY3_EVENT_ENTER:
			break;

		case KEY4_EVENT_CANCEL:
			break;
		default:
			break;
		}
		break;

	case upMANUELLED:
		switch (press)
			{
			case BE_SINGLE_PUSH:
				num++;
				break;

			case BE_DOUBBLE_PUSH:
				next_state = downMANUELLED;
				break;

			case BE_LONG_PUSH:
				next_state = AUTOLED_up;
				break;
			default:
				break;

			}
		break;
	case downMANUELLED:
		switch (press)
			{
			case BE_SINGLE_PUSH:
				num--;
				break;

			case BE_DOUBBLE_PUSH:
				next_state = upMANUELLED;
				break;

			case BE_LONG_PUSH:
				next_state = AUTOLED_up;
				break;
			default:
				break;

			}
			break;
	case AUTOLED_up:
		counter_timer++;
		switch (press)
			{
			case BE_SINGLE_PUSH:
				next_state = downMANUELLED;
				break;

			case BE_DOUBBLE_PUSH:
				next_state = AUTOLED_down;
				break;

			case BE_LONG_PUSH:
				num = 0;
				next_state = UPSTARTMENU;
				break;
			default:
				break;
			}
		if(counter_timer == 20)
		{
			num++;
			counter_timer = 0;
		}
		break;
	case AUTOLED_down:
		counter_timer++;
		switch (press)
			{
			case BE_SINGLE_PUSH:
				next_state = upMANUELLED ;
				break;

			case BE_DOUBBLE_PUSH:
				next_state = AUTOLED_up;
				break;

			case BE_LONG_PUSH:
				num = 0;
				next_state = UPSTARTMENU;
				break;
			default:
				break;
			}
		if(counter_timer == 20)
		{
			num--;
			counter_timer = 0;
		}
			break;
		default:
			break;
	// The program should never get here !
    }

	if(num == 8)
	{
		num = 0;
	}
	if(num == -1)
	{
		num = 7;
	}
    if (next_state != TS_State)	//! is set want the state mashine do after it round one time ture the program after a state is changed
    {
    	OnExit(TS_State);		//! befor it changes
		OnEnter(next_state);		//! after it changes
        TS_State = next_state;
    }

    Bi_counter(num);
    DoDisplay( TS_State, event);//!what the state mashine every time it run ture the program

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
	RIT128x96x4Clear();
}

void OnExit( State)
{

}

void DoDisplay( State, button)
{
	switch(State)// to show menu display at start i set it here
		{
		case UPSTARTMENU:
			RIT128x96x4StringDraw("ass1_LED",				2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw(" Binary counter",		2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw(" ",						2,	57, mainFULL_SCALE);
			break;
		case LED:
			RIT128x96x4StringDraw("LED on  ",				2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw(" LED Test",				2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw("LED off ", 				2,	57, mainFULL_SCALE);
			RIT128x96x4StringDraw(" Cancel to Menu",		2,	65, mainFULL_SCALE);
			break;
		case AUTOLED_up:
			RIT128x96x4StringDraw(" AUTO LED up",			2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw("one press to stop",		2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw(" dobbel = down",			2,	57, mainFULL_SCALE);
			RIT128x96x4StringDraw(" long press auto",		2,	65, mainFULL_SCALE);
			break;
		case AUTOLED_down:
			RIT128x96x4StringDraw(" AUTO LED down",			2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw("one press to stop",		2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw("dobbel = up",						2,	57, mainFULL_SCALE);
			RIT128x96x4StringDraw("long press auto",		2,	65, mainFULL_SCALE);
			break;
		case upMANUELLED:
			RIT128x96x4StringDraw(" up LED Test",			2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw("+1",						2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw("dobbel = down", 			2,	57, mainFULL_SCALE);
			RIT128x96x4StringDraw("long press auto",		2,	65, mainFULL_SCALE);
			break;
		case downMANUELLED:
			RIT128x96x4StringDraw(" down LED Test",			2,	41, mainFULL_SCALE);
			RIT128x96x4StringDraw("-1",						2,	49, mainFULL_SCALE);
			RIT128x96x4StringDraw("dobbel = up", 			2,	57, mainFULL_SCALE);
			RIT128x96x4StringDraw("long press auto",		2,	65, mainFULL_SCALE);
			break;
		default:
			break;
			// The program should never get here
		}
	switch (button)//!to see want button is pressed in all menus they are set here(debug)
		{
		case KEY0_EVENT_SELECT:
			RIT128x96x4StringDraw("Select Pressed",			0,	0, mainFULL_SCALE);
			break;

		case KEY1_EVENT_UP:
			RIT128x96x4StringDraw("Up Pressed    ",			0,	0, mainFULL_SCALE);
			break;

		case KEY2_EVENT_DOWN:
			RIT128x96x4StringDraw("Down Pressed  ",			0,	0, mainFULL_SCALE);
			break;

		case KEY3_EVENT_ENTER:
			RIT128x96x4StringDraw("Enter Pressed ",			0,	0, mainFULL_SCALE);
			break;

		case KEY4_EVENT_CANCEL:
			RIT128x96x4StringDraw("Cancel Pressed",			0,	0, mainFULL_SCALE);
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
