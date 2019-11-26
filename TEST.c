/*
 * main.c
 *
 *  Created on: Oct 28, 2019
 *      Author: Yomna Ragab
 */

#include "ADC_int.h"

void main (void)
{
    u32 buffer;
    ADC_enuminit();
    ADC_enumSetBuffer(0,&buffer);
    ADC_enumInterrupt_Enable(0);
    ADC_vidStartConv(0);
}



