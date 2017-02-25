/* 
 * File:   adc.h
 * Author: Shanee Lu
 *
 * Created on February 24, 2017, 3:47 PM
 */

#ifndef ADC_H
#define	ADC_H
#define _SUPPRESS_PLIB_WARNING 1
#include <plib.h>

    // define setup parameters for OpenADC10
    // Turn module on | ouput in integer | trigger mode auto | enable autosample
    // ADC_CLK_AUTO -- Internal counter ends sampling and starts conversion (Auto convert)
    // ADC_AUTO_SAMPLING_ON -- Sampling begins immediately after last conversion completes; SAMP bit is automatically set
    //
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
    // set AN4 and  as analog inputs
#define PARAM4	ENABLE_AN4_ANA 

    // define setup parameters for OpenADC10
    // do not assign channels to scan
#define PARAM5	SKIP_SCAN_ALL
void adc_initialize(void);
inline void handleISR();
float getADC();


#endif	/* ADC_H */

