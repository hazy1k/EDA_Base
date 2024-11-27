#ifndef _ADC_H_
#define _ADC_H_

#include "cw32l010_adc.h"
#include "cw32l010_gpio.h"

#define ADC_SAMPLE_SIZE (100)
#define ADC_REF_VALUE (1200)
#define R2           (82) //µ¥Î»£ºK¦¸//220
#define R1           (10)//43

 
void ADC_init(void);
void Get_ADC_Value(void);
	
#endif

