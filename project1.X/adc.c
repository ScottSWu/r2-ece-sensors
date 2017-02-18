/*******************************************************************************
* This file provides the functions for the ADC module 
*
* Cytron Technologies Sdn. Bhd.
*******************************************************************************/
// This file is written for PIC16F887, if other model of PIC is uses, please modify accordingly

#define _SUPPRESS_PLIB_WARNING 1
#include "adc1.h"
#include <math.h>

volatile float ADC_VALUE;
/*******************************************************************************
* PUBLIC FUNCTION: adc_initialize
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the ADC module.
*
*******************************************************************************/
void adc_initialize(void)
{
	// Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..
	

        // the ADC ///////////////////////////////////////
        // configure and enable the ADC
	CloseADC10();	// ensure the ADC is off before setting the configuration

	// define setup parameters for OpenADC10
	// Turn module on | ouput in integer | trigger mode auto | enable autosample
        // ADC_CLK_AUTO -- Internal counter ends sampling and starts conversion (Auto convert)
        // ADC_AUTO_SAMPLING_ON -- Sampling begins immediately after last conversion completes; SAMP bit is automatically set
        // ADC_AUTO_SAMPLING_OFF -- Sampling begins with AcquireADC10();
    #define PARAM1  ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF //

	// define setup parameters for OpenADC10
	// ADC ref external  | disable offset test | disable scan mode | do 1 sample | use single buf | alternate mode off
	#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
        //
	// Define setup parameters for OpenADC10
        // use peripherial bus clock | set sample time | set ADC clock divider
        // ADC_CONV_CLK_Tcy2 means divide CLK_PB by 2 (max speed)
        // ADC_SAMPLE_TIME_5 seems to work with a source resistance < 1kohm
    #define PARAM3 ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_5 | ADC_CONV_CLK_Tcy2 //ADC_SAMPLE_TIME_15| ADC_CONV_CLK_Tcy2

	// define setup parameters for OpenADC10
	// set AN0 and  as analog inputs
	#define PARAM4	ENABLE_AN0_ANA 

	// define setup parameters for OpenADC10
	// do not assign channels to scan
	#define PARAM5	SKIP_SCAN_ALL

	// use ground as neg ref for A | use AN0 for input A     
	// configure to sample AN0 
	//SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN0 ); // configure to sample AN0 
	//OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above

	EnableADC10(); // Enable the ADC
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 80);
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_2);
    mT2ClearIntFlag(); // and clear the interrupt flag
    
}
inline float handleISR(){
 // clear the interrupt flag
    mT2ClearIntFlag();
    // read the ADC
    // read the first buffer position
    ADC_VALUE = (float) ReadADC10(0);   // read the result of channel 4 conversion from the idle buffer
   // AcquireADC10(); // not needed if ADC_AUTO_SAMPLING_ON below 
    ADC_VALUE = ADC_VALUE * 78.77; //use datasheet for conversion- 512/3.25/2
    return ADC_VALUE;
    
}
//find conversion using datasheet, find pins for adc
//float adc_value(void){
    
   // return ADC_VALUE;
//}