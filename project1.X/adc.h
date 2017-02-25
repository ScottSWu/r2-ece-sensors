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

void adc_initialize(void);
inline void handleISR();
float getADC();

#endif	/* ADC_H */

