/* 
 * File:   adc1.h
 * Author: Shanee Lu
 *
 * Created on February 4, 2017, 4:13 PM
 */

#ifndef ADC1_H
#define	ADC1_H

#include <plib.h>

void adc_initialize(void);
char getRCR();
inline float handleISR();
//float adc_value(void);
//void __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ADC1_H */

