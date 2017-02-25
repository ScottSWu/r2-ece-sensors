/**********************************************************************
 *Shanee Lu
 * Reads and outputs distance using ultrasonic sensor
 *********************************************************************/

#define _SUPPRESS_PLIB_WARNING 1
#include "ultrasonic.h"
#include "config.h"
#include "global.h"
#include "adc.h"
#include <stdio.h> // need for printf() and sscanf()


//***************************************************
/*static char RCR = 'a'; //received character
unsigned char data[6] = {0};
*/
/********************************* 
    main entry point
 *********************************/
int main(void) {
    SYSTEMConfigPerformance(SYS_FREQ);

    init_ultrasonic();
    adc_initialize();
    set_low();
    
    clrscr(); //clear PuTTY screen
    home();

    while(1){
    }
}
    void __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void){
        handleISR();
    }
    
   /* UART reading
    * while (1) {
        for (l = 0; l < 6; l++) {
            RCR = getRCR();
            if (RCR == 'R') data[k = 0] = RCR; // check if start byte 'R' is met  
            if (data[0] == 'R') data[k++] = RCR; // save the data in data array
            if (k > 4) k = 4; // if the data array reached max, set the index to 4
        }
        printf("    %c%c%c", data[1], data[2], data[3]);
        start++;
        if (start == 1) {
            set_low();
        }
        count++;
        if (count % 2 == 1) {
            printf("\n\r");
        }

    }*/
    




