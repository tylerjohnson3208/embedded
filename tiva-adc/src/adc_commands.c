//*****************************************************************************
//
// adc_commands.c - Command line functionality implementation
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
//#include "qs-rgb.h"
//#include "drivers/rgb.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"
#include "adc_commands.h"
#include "driverlib/adc.h"

//*****************************************************************************
//
// Table of valid command strings, callback functions and help messages.  This
// is used by the cmdline module.
//
//*****************************************************************************
tCmdLineEntry g_psCmdTable[] =
{
    {"help",     CMD_help,      " : Display list of commands" },
    {"rgb",      CMD_adc,       " : Return the current ADC value"},
    { 0, 0, 0 }
};

//*****************************************************************************
//
// Command: help
//
// Print the help strings for all commands.
//
//*****************************************************************************
int
CMD_help(int argc, char **argv)
{
    int32_t i32Index;

    (void)argc;
    (void)argv;

    //
    // Start at the beginning of the command table
    //
    i32Index = 0;

    //
    // Get to the start of a clean line on the serial output.
    //
    UARTprintf("\nAvailable Commands\n------------------\n\n");

    //
    // Display strings until we run out of them.
    //
    while(g_psCmdTable[i32Index].pcCmd)
    {
      UARTprintf("%17s %s\n", g_psCmdTable[i32Index].pcCmd,
                 g_psCmdTable[i32Index].pcHelp);
      i32Index++;
    }

    //
    // Leave a blank line after the help strings.
    //
    UARTprintf("\n");

    return (0);
}

//*****************************************************************************
//
// Command: adc
//
// Takes one argument. Prints the integer value of the ADC (supplied as an
// argument) to the UART.
//
//*****************************************************************************
int
CMD_adc(int argc, char **argv)
{
    //
    // This command requires no parameters.
    //

	(void)argc;
	(void)argv;

    //
    // Value returned by ADC.
    //
	uint32_t adcValue;

	//
    // Enable the first sample sequencer to capture the value of channel 0 
    // when the processor trigger occurs.
    //
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0,
    ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
    ADCSequenceEnable(ADC0_BASE, 0);

    //
    // Trigger the sample sequence.
    //
    ADCProcessorTrigger(ADC0_BASE, 0);

    //
    // Wait until the sample sequence has completed.
    //
    while(!ADCIntStatus(ADC0_BASE, 0, false))
    {
    }

    //
    // Read the value from the ADC.
    //
    ADCSequenceDataGet(ADC0_BASE, 0, &adcValue);

    //
    // Print the ADC value to the UART.
    //
    UARTprintf("\nADC Value: %i\n", adcValue);
    return (0);

}
