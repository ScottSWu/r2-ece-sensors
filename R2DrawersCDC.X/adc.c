#include "adc.h"
#include "global.h"
#include <plib.h>
#define _SUPPRESS_PLIB_WARNING 1


void configADC() {
   
	// configure and enable the ADC
	CloseADC10();	// ensure the ADC is off before setting the configuration
    mPORTASetPinsAnalogIn(BIT_0 | BIT_1);
    mPORTBSetPinsAnalogIn(BIT_2 | BIT_3 | BIT_14 | BIT_15 | BIT_13);
	// define setup parameters for OpenADC10
				// Turn module on | output in integer | trigger mode auto | enable  autosample
	#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

	// define setup parameters for OpenADC10
			    // ADC ref external    | disable offset test    | enable scan mode | perform 7 samples | use one buffer | use MUXA mode
       // note: to read X number of pins you must set ADC_SAMPLES_PER_INT_X
	#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_7 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF

	// define setup parameters for OpenADC10
	// 				  use ADC internal clock | set sample time
    #define PARAM3 ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_5 | ADC_CONV_CLK_Tcy2 //ADC_SAMPLE_TIME_15| ADC_CONV_CLK_Tcy2

	// define setup parameters for OpenADC10
				// set AN4 and AN5
	#define PARAM4	ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN9_ANA | ENABLE_AN10_ANA | ENABLE_AN11_ANA

	// define setup parameters for OpenADC10
	// do not assign channels to scan
	#define PARAM5 SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15

	// use ground as neg ref for A 
	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF); // use ground as the negative reference
	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using parameter define above

	EnableADC10(); // Enable the ADC

	while ( ! mAD1GetIntFlag() ) { } // wait for the first conversion to complete so there will be valid data in ADC result registers
}