/**********************************************************************
 *Shanee Lu
 * Reads and outputs distance using ultrasonic sensors
 *********************************************************************/

#define _SUPPRESS_PLIB_WARNING 1
#include "uart_putty.h"
#include "config.h"
#include "global.h"
#include "adc.h"
#include "ultrasonic.h"
#include <plib.h>
#include <stdio.h> // need for printf() and sscanf()

/* Credit for this configuration goes to: http://hades.mech.northwestern.edu/index.php/PIC32MX:_Analog_Inputs*/

/********************************* 
    main entry point
 *********************************/
int main(void) {
    //Configure the proper PB frequency and the number of wait states
	SYSTEMConfigPerformance(SYS_FREQ);

    init_uart();
    configADC();
    init_sensors();
    
    clrscr(); //clear PuTTY screen
    home();

    while(1){
        printf("%.1f       ", (float) ReadADC10(0)/2.01);
        printf("%.1f       ", (float) ReadADC10(1)/2.01);
        printf("%.1f       ", (float) ReadADC10(2)/2.01);
        printf("\n\r");
    }
}



