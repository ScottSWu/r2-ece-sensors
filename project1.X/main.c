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

 //   init_uart();
    configADC();
    init_sensors();
    
    clrscr(); //clear PuTTY screen
    home();

    while(1){
        printf("%.1f       ", (float) ReadADC10(0)/3.11); //conversion done using datasheet- (512*3.105)/(3.3*254)
        printf("%.1f       ", (float) ReadADC10(1)/3.11); //3.105 is measured Vcc, 3.3 is power supply, 254 is max distance
        printf("%.1f       ", (float) ReadADC10(2)/3.11); //512 given in datasheet (1024/2)
        printf("\n\r");
    }
}



