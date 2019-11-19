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


void ADC_EnableDisableSeqSel(u8 control,u8 sample_seq)
{

    if (control==DISABLE)
    {
        CLR_BIT(ADC0ACTSS,sample_seq);
        //        if(SAMPLE_SEQ==SS3) ADC0ACTSS &= ~0x0008;
        //        else if(SAMPLE_SEQ==SS2) ADC0ACTSS &= ~0x0004;
        //        else if(SAMPLE_SEQ==SS1) ADC0ACTSS &= ~0x0002;
        //        else if(SAMPLE_SEQ==SS0) ADC0ACTSS &= ~0x0001;
    }
    else if(control==ENABLE)
    {
        SET_BIT(ADC0ACTSS,sample_seq);
        //        if(SAMPLE_SEQ==SS3) ADC0ACTSS |= 0x0008;
        //        else if(SAMPLE_SEQ==SS2) ADC0ACTSS |= 0x0004;
        //        else if(SAMPLE_SEQ==SS1) ADC0ACTSS |= 0x0002;
        //        else if(SAMPLE_SEQ==SS0) ADC0ACTSS |= 0x0001;
    }
}
void ADC_vidTrigger(u8 trigger,u8 sample_seq)
{
    if(trigger==SW) //ADCPSSI to set the trigger
    {
        ADC0EMUX &= ~ (0xF << 4*sample_seq);
    }
    else if (trigger==CONT)
    {
        ADC0EMUX &= ~ (0x0 << 4*sample_seq);
    }
    //    else if (CONV_TRIGGER==COMP0) //ACCTL0 reg to set the trigger
    //    {
    //        if(SAMPLE_SEQ==SS3) ADC0EMUX &= ~0x7000;
    //        else if(SAMPLE_SEQ==SS2) ADC0EMUX &= ~0x0700;
    //        else if(SAMPLE_SEQ==SS1) ADC0EMUX &= ~0x0070;
    //        else if(SAMPLE_SEQ==SS0) ADC0EMUX &= ~0x0007;
    //    }
}
void ADC_vidChannelSelection(u8* pin,u8 sample_seq)
{
    u8 i=0;
    if(sample_seq==SS3)
    {
        while (pin[i]!='\0')
        {
            ADC0SSMUX3=pin[i];
            i++;
        }
    }
    else if(sample_seq==SS2)
    {
        while (pin[i]!='\0')
        {
            ADC0SSMUX2=pin[i]<<(4*i);
            i++;
        }
    }
    else if(sample_seq==SS1)
    {
        while (pin[i]!='\0')
        {
            ADC0SSMUX1=pin[i]<<(4*i);
            i++;
        }
    }
    else if(sample_seq==SS0)
    {
        while (pin[i]!='\0')
        {
            ADC0SSMUX0=pin[i]<<(4*i);
            i++;
        }
    }

}
void ADC_vidSSCTL(u8 seq,u8 no_of_channels)
{
    //SINGLE_ACCESS
    if(seq==SS3) ADC0SSCTL3=0x6;
    else if(seq==SS2) ADC0SSCTL2=0x6<<((4*no_of_channels)+1);
    else if(seq==SS1) ADC0SSCTL1=0x6<<((4*no_of_channels)+1);
    else if(seq==SS0) ADC0SSCTL0=0x6<<((4*no_of_channels)+1);
}


