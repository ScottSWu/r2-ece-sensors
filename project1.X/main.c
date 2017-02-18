/**********************************************************************
 *Shanee Lu
 * Reads and outputs distance using ultrasonic sensor
 *********************************************************************/

#define _SUPPRESS_PLIB_WARNING 1
#include "ultrasonic.h"
#include "config.h"
#include "global.h"
#include <stdio.h> // need for printf() and sscanf()


//***************************************************
static char RCR = 'a'; //received character
unsigned char data[6] = {0};

/********************************* 
    main entry point
 *********************************/
int main(void) {
    SYSTEMConfigPerformance(SYS_FREQ);

    init_ultrasonic();
    // PuTTY
    clrscr(); //clear PuTTY screen
    home();

    unsigned int k, l = 0;

    while (1) {
        for (l = 0; l < 6; l++) {
            RCR = getRCR();
            if (RCR == 'R') data[k = 0] = RCR; // check if start byte 'R' is met  
            if (data[0] == 'R') data[k++] = RCR; // save the data in data array
            if (k > 4) k = 4; // if the data array reached max, set the index to 4
        }
        printf("Distance: %c%c%c in\n\r", data[1], data[2], data[3]);

    }

}

