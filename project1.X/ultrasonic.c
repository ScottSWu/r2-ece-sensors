#define _SUPPRESS_PLIB_WARNING 1
#include "ultrasonic.h"
#include "global.h"

void init_ultrasonic(){

    // By default, MPLAB XC32's libraries use UART2 for STDOUT.
    // This means that formatted output functions such as printf()
    // will send their output to UART2
     __XC_UART = 2;
     mPORTASetPinsDigitalIn(BIT_1);
     mPORTASetPinsDigitalOut(BIT_3);
     mPORTASetBits(BIT_3);
     
    // specify PPS group, signal, logical pin name
    PPSInput (2, U2RX, RPA1); //Assign U2RX to pin RPA1 -- Physical pin 3 on 28 PDIP
    PPSOutput(4, RPB10, U2TX); //Assign U2TX to pin RPB10 -- Physical pin 21 on 28 PDIP
   
    // init the uart2
    UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART2, PB_FREQ, BAUDRATE);
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    
}

/*char getRCR(){
    while (!DataRdyUART1());
    char RCR = getcUART1();
    return RCR;
}
*/
void set_low(){
    #define dTime_us 40000000/2000000
    unsigned int j;
    j = dTime_us * 22;
    WriteCoreTimer(0);
    while (ReadCoreTimer() < j);
    mPORTASetPinsDigitalIn(BIT_3); 
    
}
