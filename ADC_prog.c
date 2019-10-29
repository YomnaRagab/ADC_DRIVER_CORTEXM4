/*
 * ADC_prog.c
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
enumerr ADC_enumSetPin(u8 pin)
{
    u8 desired_port;
    if ((pin == AIN0) || (pin == AIN1) || (pin == AIN2) || (pin == AIN3) || (pin == AIN8) || (pin == AIN9)) desired_port=PORTE;
    else if ((pin == AIN4) || (pin == AIN5) || (pin == AIN6) || (pin == AIN7)) desired_port=PORTD;
    else if ((pin == AIN10) || (pin == AIN11) ) desired_port=PORTB;
    else return(NOKAY);
    SET_BIT(RCGCGPIO,desired_port); // 1) activate clock for the specific port
    GPIO_enumSetPinDir(pin,INPUT);  // 2) make the desired pin input
    ADC_vidSetAlternateFunc(pin,desired_port); // 3) enable alternate function
    ADC_vidDisableDEN(pin,desired_port); //4) disable digital I/O
    ADC_vidEnAnalogFunc(pin,desired_port); // 5) enable analog function
    RCGC0|=0x00010000; // 6)ACTIVATE ADC0
    ADC_vidSampleSpeed(); // 7) configure for MAX_SPEED
    ADC_SeqSelPriority(); // 8) the chosen sequencer is highest priority
    ADC_EnableDisableSeqSel(DISABLE); // 9) disable sample sequencer which was chosen
    ADC_vidTrigger(); // 10) SELECT THE trigger
    ADC_vidChannelSelection(pin);// 11)Channel selection to sample
    ADC0SSCTL3=0x006;   //12)Flag to be set
    //3--> temp sesnor 2-->IE (to make RIS bit =1 when sampling is done
    // 1-->END0 (it's the last sample) 0--> D0 diffrential mode
    ADC_EnableDisableSeqSel(ENABLE); // 13) enable sample sequencer which was chosen
    return(OKAY);
}
enumerr ADC_enumGetData(u16* DATA)
{
    if(CONV_TRIGGER==SW) ADC0PSSI = 0x0008;            // 1) initiate SS3
    else if (CONV_TRIGGER==COMP0)
    {
        SET_BIT(ACCTL0,11); //Trigger Output Enable
        CLR_BIT(ACCTL0,9); //9:10 +ve source is the internal refrence
        SET_BIT(ACCTL0,10);
        SET_BIT(ACCTL0,7); //Trigger Sense Level Value -->1 ,An ADC event is generated if the comparator output is High.
    }
    while((ADC0RIS&0x08)==0){};   // 2) wait for conversion done

    DATA = ADC0SSFIFO3&0xFFF;   // 3) read result

    ADC0ISC = 0x0008;             // 4) acknowledge completion
}



