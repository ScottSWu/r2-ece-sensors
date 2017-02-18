/**********************************************************************
*
* Set up UART2 and demo i/o
 * Using Sparkfun CP2102 interface with
 *   CP2102 TX pin hooked to MCU pin 22
 *   CP2102 RX pin hooked to MCU pin 21
* modified by Bruce R land
* May 2014
*********************************************************************/

#define _SUPPRESS_PLIB_WARNING 1
#include "adc1.h"
//include "display1.h"
#include <stdio.h> // need for printf() and sscanf()
#define	SYS_FREQ 40000000
//  Configuration Bit settings
//  System Clock = 40 MHz,  Peripherial Bus = 40 MHz
//  Internal Osc w/PLL FNOSC = FRCPLL
//  Input Divider    2x Divider FPLLIDIV
//  Multiplier      20x Multiplier FPLLMUL
//  Output divider   2x Divider FPLLODIV
//  peripherial bus divider FPBDIV = 1
//  WDT disabled
//  Other options are don't care
//
#pragma config FNOSC = FRCPLL, POSCMOD = OFF, FSOSCEN = OFF, OSCIOFNC = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF
// frequency we're running at


// UART parameters
#define BAUDRATE 9600 // must match PC end
#define PB_DIVISOR (1 << OSCCONbits.PBDIV) // read the peripheral bus divider, FPBDIV
#define PB_FREQ SYS_FREQ/PB_DIVISOR // periperhal bus frequency

// useful ASCII/VT100 macros for PuTTY
#define clrscr() printf( "\x1b[2J")
#define home()   printf( "\x1b[H")
#define pcr()    printf( '\r')
#define crlf     putchar(0x0a); putchar(0x0d);
#define max_chars 10 // for input buffer


//***************************************************
static char RCR='a'; 		//received character
int num ;
char buffer[64];
volatile float ADC_VALUE;
unsigned char data[6] = {0};
/********************************* 
	main entry point
*********************************/
int main ( void )
{   
    SYSTEMConfigPerformance(SYS_FREQ);
    int count, items, num_char;
     __XC_UART = 2;
     mPORTASetPinsDigitalIn(BIT_1);
    /* 	Initialize PPS */
    // Data sheet: 
    // http://people.ece.cornell.edu/land/courses/ece4760/PIC32/Microchip_stuff/2xx_datasheet.pdf
    // data sheet table 11-1 gives input pin mapping
    // data sheet table 11.2 gives output pin mapping
    // Also Section 12 of PIC32MX Family Reference Manual
    // http://hades.mech.northwestern.edu/images/2/21/61132B_PIC32ReferenceManual.pdf
    // macro defs
    // http://quadcopter-miami-ece.googlecode.com/svn/trunk/mpide-0023-windows-20120903/hardware/pic32/compiler/pic32-tools/pic32mx/include/peripheral/pps.h
    //
    // specify PPS group, signal, logical pin name
    PPSInput (2, U2RX, RPA1); //Assign U2RX to pin RPB11 -- Physical pin 22 on 28 PDIP
    PPSOutput(4, RPB10, U2TX); //Assign U2TX to pin RPB10 -- Physical pin 21 on 28 PDIP
    
    PPSInput (3, U1RX, RPA2); //Assign U1RX to pin RPA2 -- Physical pin 9 on 28 PDIP
    PPSOutput(1, RPA0, U1TX); //Assign U1TX to pin RPA0 -- Physical pin 2 on 28 PDIP

    ANSELA =0; //make sure analog is cleared
    ANSELB =0;
   
    // init the uart2
    UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART2, PB_FREQ, BAUDRATE);
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART1, PB_FREQ, BAUDRATE);
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));



    // PuTTY
    clrscr();  //clear PuTTY screen
    home();
    // By default, MPLAB XC32's libraries use UART2 for STDOUT.
    // This means that formatted output functions such as printf()
    // will send their output to UART2
    
    unsigned int k,l = 0;
    
    while(1){
        for (l=0 ; l<6 ; l++)
            {
            RCR = getRCR();
			if(RCR == 'R') data[k=0] = RCR;			// check if start byte 'R' is met  
			if(data[0] == 'R') data[k++] = RCR;		// save the data in data array
			if (k>4) k = 4;								// if the data array reached max, set the index to 4
			}
        printf("Distance:");
        printf(" %c", data[1]);
        printf(" %c", data[2]);
        printf(" %c\n\r", data[3]);
	//}
    }
   /* adc_initialize();
    while(1){
        printf("Distance: \n\r");
        sprintf(buffer, "%d\n\r", ADC_VALUE);
        printf(buffer);
    }
	*/
}

/* void __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler()
{
       ADC_VALUE = handleISR();
}*/

char getRCR(){
   //while(!UARTReceivedDataIsAvailable(UART1)){};
    //receive it
   // RCR = UARTGetDataByte(UART1);
    while (!DataRdyUART1());
    RCR = getcUART1();
    // wait for clear transmitter (always true in this code)
  /* while(!UARTTransmitterIsReady(UART1)){};
    // and echo it
    UARTSendDataByte(UART1, RCR);
    //}
   * */
    return RCR;
}