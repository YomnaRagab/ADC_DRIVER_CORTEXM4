/*
 * ADC_utils.c
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */
#include "std_types.h"
#include "GPIO_Priv.h"
#include "GPIO_Mem_Map.h"
#include "GPIO_Int.h"
#include "ADC_memory_map.h"
#include "ADC_int.h"
#include "ADC_priv.h"
#include "ADC_confg.h"
extern u32 PORTS_BASES[PORTS_NUMBER];

void ADC_vidSetAlternateFunc(u8 pin,u8 desired_port)
{
    if ((pin== AIN8)||(pin== AIN11)) GPIOAFSEL(desired_port) |=0x20;
    else if ((pin== AIN9)||(pin== AIN10)) GPIOAFSEL(desired_port) |=0x10;
    else if ((pin== AIN0)||(pin== AIN4)) GPIOAFSEL(desired_port) |=0x08;
    else if ((pin== AIN1)||(pin== AIN5)) GPIOAFSEL(desired_port) |=0x04;
    else if ((pin== AIN2)||(pin== AIN6)) GPIOAFSEL(desired_port) |=0x02;
    else if ((pin== AIN3)||(pin== AIN7)) GPIOAFSEL(desired_port) |=0x01;
}
void ADC_vidDisableDEN(u8 pin,u8 desired_port)
{
    if ((pin== AIN8)||(pin== AIN11)) GPIODEN(desired_port) &= ~0x20;
    else if ((pin== AIN9)||(pin== AIN10)) GPIODEN(desired_port) &= ~0x10;
    else if ((pin== AIN0)||(pin== AIN4)) GPIODEN(desired_port)  &= ~0x08;
    else if ((pin== AIN1)||(pin== AIN5)) GPIODEN(desired_port)  &= ~0x04;
    else if ((pin== AIN2)||(pin== AIN6)) GPIODEN(desired_port)  &= ~0x02;
    else if ((pin== AIN3)||(pin== AIN7)) GPIODEN(desired_port)  &= ~0x01;
}
void ADC_vidEnAnalogFunc(u8 pin,u8 desired_port)
{
    if ((pin== AIN8)||(pin== AIN11)) GPIOAMSEL(desired_port)|=0x20;
    else if ((pin== AIN9)||(pin== AIN10)) GPIOAMSEL(desired_port)|=0x10;
    else if ((pin== AIN0)||(pin== AIN4)) GPIOAMSEL(desired_port)|=0x08;
    else if ((pin== AIN1)||(pin== AIN5)) GPIOAMSEL(desired_port)|=0x04;
    else if ((pin== AIN2)||(pin== AIN6)) GPIOAMSEL(desired_port)|=0x02;
    else if ((pin== AIN3)||(pin== AIN7)) GPIOAMSEL(desired_port)|=0x01;
}
void ADC_vidSampleSpeed(void)
{
    if (SAMPLE_SPEED == SS_125k) RCGC0 &= ~0x00000300;
    else if (SAMPLE_SPEED == SS_250k) RCGC0 &= ~0x00000200;
    else if (SAMPLE_SPEED == SS_500k) RCGC0 &= ~0x00000100;
    else if (SAMPLE_SPEED == SS_1M) RCGC0 &= ~0x00000000;
}
void ADC_SeqSelPriority(void)
{
    if(SAMPLE_SEQ==SS3) ADC0SSPRI =0x0123; //priority for ss3
    else if(SAMPLE_SEQ==SS2) ADC0SSPRI =0x1023; //priority for ss2
    else if(SAMPLE_SEQ==SS1) ADC0SSPRI =0x2103; //priority for ss1
    else if(SAMPLE_SEQ==SS0) ADC0SSPRI =0x3210; //priority for ss0
}
void ADC_EnableDisableSeqSel(u8 control)
{

    if (control==DISABLE)
    {
        CLR_BIT(ADC0ACTSS,SAMPLE_SEQ);
        //        if(SAMPLE_SEQ==SS3) ADC0ACTSS &= ~0x0008;
        //        else if(SAMPLE_SEQ==SS2) ADC0ACTSS &= ~0x0004;
        //        else if(SAMPLE_SEQ==SS1) ADC0ACTSS &= ~0x0002;
        //        else if(SAMPLE_SEQ==SS0) ADC0ACTSS &= ~0x0001;
    }
    else if(control==ENABLE)
    {
        SET_BIT(ADC0ACTSS,SAMPLE_SEQ);
                //        if(SAMPLE_SEQ==SS3) ADC0ACTSS |= 0x0008;
                //        else if(SAMPLE_SEQ==SS2) ADC0ACTSS |= 0x0004;
                //        else if(SAMPLE_SEQ==SS1) ADC0ACTSS |= 0x0002;
                //        else if(SAMPLE_SEQ==SS0) ADC0ACTSS |= 0x0001;
    }
}
void ADC_vidTrigger(void)
{
    if(CONV_TRIGGER==SW) //ADCPSSI to set the trigger
    {
        if(SAMPLE_SEQ==SS3) ADC0EMUX &= ~0xF000;
        else if(SAMPLE_SEQ==SS2) ADC0EMUX &= ~0x0F00;
        else if(SAMPLE_SEQ==SS1) ADC0EMUX &= ~0x00F0;
        else if(SAMPLE_SEQ==SS0) ADC0EMUX &= ~0x000F;
    }
    else if (CONV_TRIGGER==CONT)
    {
        if(SAMPLE_SEQ==SS3) ADC0EMUX &= ~0x0000;
        else if(SAMPLE_SEQ==SS2) ADC0EMUX &= ~0x0000;
        else if(SAMPLE_SEQ==SS1) ADC0EMUX &= ~0x0000;
        else if(SAMPLE_SEQ==SS0) ADC0EMUX &= ~0x0000;
    }
    else if (CONV_TRIGGER==COMP0) //ACCTL0 reg to set the trigger
    {
        if(SAMPLE_SEQ==SS3) ADC0EMUX &= ~0x7000;
        else if(SAMPLE_SEQ==SS2) ADC0EMUX &= ~0x0700;
        else if(SAMPLE_SEQ==SS1) ADC0EMUX &= ~0x0070;
        else if(SAMPLE_SEQ==SS0) ADC0EMUX &= ~0x0007;
    }
}
void ADC_vidChannelSelection(u8 pin)
{
    if(SAMPLE_SEQ==SS3) ADC0SSMUX3=pin;
   // if(SAMPLE_SEQ==SS3) ADC0SSMUX0=
}


