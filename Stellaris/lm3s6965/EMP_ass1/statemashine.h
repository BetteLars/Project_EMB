/**
 * statemashine.h
 *
 *  Created on: 04/10/2012
 *      Author: Lars
 */

#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_
//! This is the @param enum of the states are so need a state more here is to make it
enum states { UPSTARTMENU, LED, AUTOLED, upMANUELLED,downMANUELLED, MAXSTATES };

// forward function declarations
void DoDisplay( int, int );
void OnEnter( int);
void OnExit( int);
int statemashine(int);

//------------------------------

#endif /* STATEMASHINE_H_ */
