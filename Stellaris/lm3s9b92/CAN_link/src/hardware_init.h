/*
 * hardware_init.h
 *
 *  Created on: 27/02/2013
 *      Author: Lasse
 */

#ifndef HARDWARE_INIT_H_
#define HARDWARE_INIT_H_

void initHW(void);

void init_clk_system(void);
/*****************************************************************************
*   Input    : 	-
*   Function : Set the system clock to 50 Mhz.
*****************************************************************************/

void enable_global_int();
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : Enable global interrupt
*****************************************************************************/

void disable_global_int();
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : Disable global interrupt
*****************************************************************************/
#endif /* HARDWARE_INIT_H_ */
