//*****************************************************************************
//
// main.c - Main program for the ADC program with UART terminal access.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"
#include "driverlib/uart.h"
#include "adc_commands.h"

//*****************************************************************************
//
// A demonstration of the Tiva C Series LaunchPad (EK-TM4C123GXL)
// ADC capabilities.
//
// The system will initialize, first showing a red LED. Once initialization is
// complete, the system will begin measuring the ADC0 input. 
//
// The system can be controlled via a command line provided via the UART.
// Configure your host terminal emulator for 115200, 8-N-1 to access this
// feature.
//
// - Command 'help' generates a list of commands and helpful information.
// - Command 'adc' will return the current value measured by the ADC.
//
//*****************************************************************************

//*****************************************************************************
//
// The user LEDs for indicating status.
//
//*****************************************************************************
#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

//*****************************************************************************
//
// Input buffer for the command line interpreter.
//
//*****************************************************************************
static char g_cInput[APP_INPUT_BUF_SIZE];

//***************************************************************************** //
// Variable for returned command status. 
//
//*****************************************************************************
int32_t i32CommandStatus;

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

int main()
{
    // Initialization
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);

	// Set the red LED pin high, others low
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_RED);
	ROM_SysCtlDelay(5000000);

    // Set up the ADC
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {
    }

    //
    // Enable and Initialize the UART.
    //
    ConfigureUART();

    UARTprintf("Welcome to the ADC program!\n");
    UARTprintf("Type 'help' for a list of commands\n");
    UARTprintf("> ");


	// Initialization complete, set green LED pin high, others low
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_GREEN);
   	while(1) {
		UARTprintf("\n");

		//
		// Peek to see if a full command is ready for processing.
		//
		while(UARTPeek('\r') == -1)
		{
		    //
            // millisecond delay.  A SysCtlSleep() here would also be OK.
            //
            SysCtlDelay(SysCtlClockGet() / (1000 / 3));
		}

		//
		// A '\r' was detected. Get the input from the user.
		//
		UARTgets(g_cInput,sizeof(g_cInput));

		//
		// Pass the line from the user to the command processor.
		// It is parsed and valid commands exectuted.
		//
		i32CommandStatus = CmdLineProcess(g_cInput);
 
        ////
        //// Enable the first sample sequencer to capture the value of channel 0 
		//// when the processor trigger occurs.
        ////
        //ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
        //ADCSequenceStepConfigure(ADC0_BASE, 0, 0,
        //ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
        //ADCSequenceEnable(ADC0_BASE, 0);

        ////
        //// Trigger the sample sequence.
        ////
        //ADCProcessorTrigger(ADC0_BASE, 0);

        ////
        //// Wait until the sample sequence has completed.
        ////
        //while(!ADCIntStatus(ADC0_BASE, 0, false))
        //{
        //}

        ////
        //// Read the value from the ADC.
        ////
        //ADCSequenceDataGet(ADC0_BASE, 0, &adcValue);
	}
}
