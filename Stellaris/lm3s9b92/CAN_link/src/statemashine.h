/**
 * statemashine.h
 *
 *  Created on: 04/10/2012
 *      Author: Lars
 */

#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_
#include "inc/emp_type.h"
//! This is the @param enum of the states are so need a state more here is to make it
enum states 	{ CAN_menu,			MAXSTATES};
enum sup_states	{OFF = 0, ON = 1,	MAXSUBSTATES};


extern INT8U buffer[32];
// forward function declarations
void DoDisplay( int, int );
void OnEnter( int);
void OnExit( int);
int statemashine(int);

//------------------------------

#endif /* STATEMASHINE_H_ */
