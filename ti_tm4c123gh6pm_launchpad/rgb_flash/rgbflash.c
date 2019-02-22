#ifndef __NO_SYSTEM_INIT
void SystemInit()
{}
#endif

#include "driverlib/sysctl.c"
#include "driverlib/gpio.c"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

void main()
{

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);
    
    //
    // Turn on the LED
    //
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);
    
    //
    // Delay for a bit
    //
    SysCtlDelay(2000000);

    while(1)
    {
        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);
    
        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
    
        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, BLUE_LED);
    
        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
        
        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, GREEN_LED);
    
        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
    }
}
