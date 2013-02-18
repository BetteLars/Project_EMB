/*
 * binarycounter.c
 *
 *  Created on: 14/02/2013
 *      Author: Lasse
 */
#include "binarycounter.h"
#include "inc\lm3s6965.h"


void Bi_counter(char value)
{
	switch( value )
	    {
	case 0:
		//! PD6 					: LED1 RED off
		GPIO_PORTD_DATA_R |= 0x40;
		//! PG0+PG1 				: LED2 YELLOW + LED3 GREEN off
		GPIO_PORTG_DATA_R |= 0x03;
		break;
	case 1:
		//! PD6 					: LED1 RED on
		GPIO_PORTD_DATA_R &= ~(0x40);
		//! PG0+PG1 				: LED2 YELLOW + LED3 GREEN off
		GPIO_PORTG_DATA_R |= 0x03;
		break;
	case 2:
		//! PD6 					: LED1 RED off
		GPIO_PORTD_DATA_R |= 0x40;
		//! PG0 					: LED2 YELLOW on
		GPIO_PORTG_DATA_R &= ~(0x01);
		//! PG1						: LED3 GREEN off
		GPIO_PORTG_DATA_R |= 0x02;
		break;
	case 3:
		//! PD6 					: LED1 RED on
		GPIO_PORTD_DATA_R &= ~(0x40);
		//! PG0 					: LED2 YELLOW on
		GPIO_PORTG_DATA_R &= ~(0x01);
		//! PG1 					: LED3 GREEN off
		GPIO_PORTG_DATA_R |= 0x02;
		break;
	case 4:
		//! PD6 					: LED1 RED off
		GPIO_PORTD_DATA_R |= 0x40;
		//! PG0 					: LED2 Yellow off
		GPIO_PORTG_DATA_R |= 0x01;
		//! PG1 					: LED3 GREEN on
		GPIO_PORTG_DATA_R &= ~(0x02);
		break;
	case 5:
		//! PD6 					: LED1 RED on
		GPIO_PORTD_DATA_R &= ~(0x40);
		//! PG0 					: LED2 Yellow off
		GPIO_PORTG_DATA_R |= 0x01;
		//! PG1						:LED3 GREEN on
		GPIO_PORTG_DATA_R &= ~(0x02);

		break;
	case 6:
		//! PG0+PG1					: LED2 YELLOW on + LED3 GREEN on
		GPIO_PORTG_DATA_R &= ~(0x03);
		//! PD6 					: LED1 RED off
		GPIO_PORTD_DATA_R |= 0x40;
		break;
	case 7:
		//! PD6 					: LED1 RED
		GPIO_PORTD_DATA_R &= ~(0x40);
		//! PG0 					: LED2 YELLOW
		GPIO_PORTG_DATA_R &= ~(0x01);
		//! PG1 					: LED3 GREEN
		GPIO_PORTG_DATA_R &= ~(0x02);
		break;
	    }

}

