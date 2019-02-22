//*****************************************************************************
//
// adc_commands.h - Prototypes for the evaluation board command line utils.
//
//*****************************************************************************

#ifndef __ADC_COMMANDS_H__
#define __ADC_COMMANDS_H__

//*****************************************************************************
//
// Defines for the command line argument parser provided as a standard part of
// TivaWare.  adc application uses the command line parser to extend
// functionality to the serial port.
//
//*****************************************************************************

#define CMDLINE_MAX_ARGS 3

//*****************************************************************************
//
// Defines for the command line argument parser provided as a standard part of
// TivaWare.  adc application uses the command line parser to extend
// functionality to the serial port.
//
//*****************************************************************************

#define APP_INPUT_BUF_SIZE 128

//*****************************************************************************
//
// Declaration for the callback functions that will implement the command line
// functionality.  These functions get called by the command line interpreter
// when the corresponding command is typed into the command line.
//
//*****************************************************************************
extern int CMD_help (int argc, char **argv);
extern int CMD_adc (int argc, char **argv);

#endif //__ADC_COMMANDS_H__
