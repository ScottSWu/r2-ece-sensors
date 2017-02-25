#define _SUPPRESS_PLIB_WARNING 1
#include "adc.h"
#include "global.h"
#include <math.h>

volatile float ADC_VALUE, a = 0;
volatile unsigned int c = 1, count = 0;



void adc_initialize(void) {
    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..

    // configure and enable the ADC
    CloseADC10(); // ensure the ADC is off before setting the configuration

    mPORTASetPinsAnalogIn(BIT_0 | BIT_4);



    // use ground as neg ref for A | use AN4 for input A     
    // configure to sample AN4 
    //SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 ); // configure to sample AN4 
    SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4); // configure to sample AN4 
    OpenADC10(PARAM1, PARAM2, PARAM3, PARAM4, PARAM5); // configure ADC using the parameters defined above

    EnableADC10(); // Enable the ADC
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 40000);
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_2);
    mT2ClearIntFlag(); // and clear the interrupt flag
    INTEnableSystemMultiVectoredInt();


}

inline void handleISR() {


   c = 1 - c;
    if (c == 0) {

        SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4);
        OpenADC10(PARAM1, PARAM2, PARAM3, ENABLE_AN4_ANA, PARAM5);
        EnableADC10();

        // clear the interrupt flag
        mT2ClearIntFlag();
        // read the ADC
        // read the first buffer position
        ADC_VALUE = (float) ReadADC10(0); // read the result of channel 4 conversion from the idle buffer
        AcquireADC10();
        printf("%.1f in     ", getADC());       
        count++;
        if (count % 2 == 0)
            printf("\n\r");
    } else {
        SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN0);
        OpenADC10(PARAM1, PARAM2, PARAM3, ENABLE_AN0_ANA, PARAM5);
        EnableADC10();

        // clear the interrupt flag
        mT2ClearIntFlag();
        // read the ADC
        // read the first buffer position
        ADC_VALUE = (float) ReadADC10(0); // read the result of channel 4 conversion from the idle buffer
        AcquireADC10();
        printf("%.1f in     ", getADC());
        count++;
        if (count % 2 == 0)
            printf("\n\r");
    }
}

float getADC() {
    a = ADC_VALUE / 2; //use datasheet for conversion-
    return a;
}
