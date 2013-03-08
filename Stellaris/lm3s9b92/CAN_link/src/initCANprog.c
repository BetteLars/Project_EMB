#include "inc/lm3s9b92.h"

#include "inc/emp_type.h"

#include "utils/uartstdio.h"


#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_ints.h"
#include "driverlib/uart.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"




//*****************************************************************************
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//*****************************************************************************
/*void Init_UART(void)
{
	volatile INT8S dummy;
	// Enable GPIO port A which is used for UART0 pins
	// Enable the GPIO port that is used for the on-board.
		SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
		dummy = SYSCTL_RCGC2_R;
	// Enable GPIO port A which is used for UART0 pins


    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
		// Set GPIO A0 and A1 as UART pins. Side 412 viser eksempel
		GPIO_PORTA_AFSEL_R	|= 0x03; // 1 for "alternate function"
		GPIO_PORTA_DEN_R	|= 0x03;


    // Select the alternate (UART) function for these pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for console I/O.
    UARTStdioInit(0);
    
    UARTprintf("ho");
}*/

void Init_CAN(void)
{
    // For this example CAN0 is used with RX and TX pins on port A4 and A5.
    // The actual port and pins used may be different on your part, consult
    // the data sheet for more information.
    // GPIO port A needs to be enabled so these pins can be used.
    // TODO: change this to whichever GPIO port you are using
    //
    // Already done in initialisation
        //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the GPIO pin muxing to select CAN0 functions for these pins.
    // This step selects which alternate function is available for these pins.
    // This is necessary if your part supports GPIO pin function muxing.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using
    GPIOPinConfigure(0x00001005);//GPIO_PA4_CAN0RX
    GPIOPinConfigure(0x00001401);//GPIO_PA5_CAN0TX

    // Enable the alternate function on the GPIO pins.  The above step selects
    // which alternate function is available.  This step actually enables the
    // alternate function instead of GPIO for these pins.
    // TODO: change this to match the port/pin you are using
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    
    // The GPIO port and pins have been set up for CAN.  The CAN peripheral
    // must be enabled.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    // Initialize the CAN controller
    CANInit(CAN0_BASE);

    // Set up the bit rate for the CAN bus.  This function sets up the CAN
    // bus timing for a nominal configuration.  You can achieve more control
    // over the CAN bus timing by using the function CANBitTimingSet() instead
    // of this one, if needed.
    // In this example, the CAN bus is set to 500 kHz.  In the function below,
    // the call to SysCtlClockGet() is used to determine the clock rate that
    // is used for clocking the CAN peripheral.  This can be replaced with a
    // fixed value if you know the value of the system clock, saving the extra
    // function call.  For some parts, the CAN peripheral is clocked by a fixed
    // 8 MHz regardless of the system clock in which case the call to
    // SysCtlClockGet() should be replaced with 8000000.  Consult the data
    // sheet for more information about CAN peripheral clocking.
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

    // Enable interrupts on the CAN peripheral.  This example uses static
    // allocation of interrupt handlers which means the name of the handler
    // is in the vector table of startup code.  If you want to use dynamic
    // allocation of the vector table, then you must also call CANIntRegister()
    // here.
    //
    // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
    //
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    // Enable the GPIOB interrupt and the CAN interrupt on the processor (NVIC).
    IntEnable(INT_GPIOB);
    IntEnable(INT_CAN0);

    // Enable the CAN for operation.
    CANEnable(CAN0_BASE);
}
