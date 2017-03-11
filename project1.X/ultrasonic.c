#include "ultrasonic.h"
#include "global.h"
#include <plib.h>

void init_sensors(){
    #define dTime_us SYS_FREQ/2000000
    unsigned int j;
    j = dTime_us * 22;
    WriteCoreTimer(0);
    while (ReadCoreTimer() < j);
    mPORTBSetPinsDigitalIn(BIT_9); 
    
}
