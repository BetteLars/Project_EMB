/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp_type.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Definements of variable types.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _EMP_TYPE_H
  #define _EMP_TYPE_H

/*****************************    Defines    *******************************/
//*****************************************************************************
//
// Define a boolean type, and values for true and false.
//
//*****************************************************************************
typedef unsigned char tBoolean;

//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
//*****************************************************************************
//
// Define char int short long longlong float and double
//
//*****************************************************************************

typedef unsigned char		BOOLEAN;
typedef unsigned char		INT8U;     /* Unsigned  8 bit quantity              */
typedef signed   char		INT8S;     /* Signed    8 bit quantity              */
typedef unsigned int		INT16U;    /* Unsigned 16 bit quantity              */
typedef signed   int		INT16S;    /* Signed   16 bit quantity              */
//typedef unsigned short		INT16U;    /* Unsigned 16 bit quantity              */
//typedef signed   short		INT16S;    /* Signed   16 bit quantity              */
typedef unsigned long		INT32U;    /* Unsigned 32 bit quantity              */
typedef signed   long		INT32S;    /* Signed   32 bit quantity              */
typedef unsigned long long	INT64U;    /* Unsigned 64 bit quantity              */
typedef signed   long long	INT64S;    /* Signed   64 bit quantity              */
typedef float				FP32;      /* Single precision floating point       */
typedef double				FP64;      /* Double precision floating point       */



/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif
