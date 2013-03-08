/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: systick_int.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090831  KHA   Module created.
*
*****************************************************************************/


/***************************** Include files *******************************/
#include "C:/StellarisWare/inc/lm3s6965.h"
#include "inc/emp_type.h"

/*****************************    Defines    *******************************/


#define SYSTICK_RELOAD_VALUE 500000

// Missing definemens in lm3s6965.h file
#define NVIC_INT_CTRL_PEND_SYST  	0x04000000  // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 	0x02000000  // Unpend a systick int

#define SYSTICK_PRIORITY		0x7E



#define PF1		1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S   ticks;


/*****************************   Functions   *******************************/


void init_systick(void)
{
	// Systick control and status register, NVIC_ST_CTRL_R
	// Systick reload register, NVIC_ST_RELOAD_R
	// Systick current value register, NVIC_ST_CURRENT_R
	// SYSTICK Calibration Value Register, NVIC_ST_CAL_R

	// Disable systick timer
	NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);
	// Set current systick counter to reload value
	NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
	// Set Reload value, Systick reload register 
	NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;
	// NVIC systick setup, vector number 15
	// Clear pending systick interrupt request
	NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;
	// Set systick priority to 0x10, first clear then set. 
	NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
	NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));
	// Select systick clock source, Use core clock
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
	// Enable systick interrupt
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
	// Enable and start timer
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}


void systick_isr(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // Mark timer tick.
  ticks++;
}

