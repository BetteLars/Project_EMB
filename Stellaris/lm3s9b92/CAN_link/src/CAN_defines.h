/*
 * CAN_defines.h
 *
 *  Created on: 07/03/2013
 *      Author: Lasse
 */

#ifndef CAN_DEFINES_H_
#define CAN_DEFINES_H_

/*****************************    Defines    *******************************/
//out
#define INDICATER		0x14//blue -left,right
#define LIGHT 			0x18//blue -long,peer,povk
#define IGNITION		0x1C//blue
#define WIPER_ROBOT		0x20//blue
#define HOWEL_BREAK		0x24//blue
#define HORN1			0x28//blue
//in
#define SPEED			0x0D//red
#define RPM				0x0C//red
#define FUEL			0x2F//red
#define COOLER_TEMP		0x05//red
#define DISTENCECOUNTER 0x2C//blue -global,trip
#define MALFUNCTION		0x21//red
#define ENGINE_RUNTIME	0x5C//red
#define HORN2			0x30//blue
#define ANBIENT_TEMP	0x4A//red


#endif /* CAN_DEFINES_H_ */
