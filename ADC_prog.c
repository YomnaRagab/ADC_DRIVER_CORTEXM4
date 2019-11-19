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
#include "GPIO_Utils.h"
extern u32 PORTS_BASES[PORTS_NUMBER];
extern strGroupInfo adc_groups[NUMOFGROUPS];
extern strModuleInfo adc_confg[NUMOFMODULES];

enumerr ADC_enuminit(void)
{
    u8 i,j,desired_port;
    for (i=0; i<NUMOFMODULES; i++)
    {
        for (j=0; j<adc_confg[i].no_of_inp_channels; j++) //setup pins to be ADC
        {
            if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN0) || (adc_groups[adc_confg[i].group_ID].ss_pins[j]== AIN1) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN2) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN3) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN8) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN9)) desired_port=PORTE;
            else if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN4) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN5) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN6) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN7)) desired_port=PORTD;
            else if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN10) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN11) ) desired_port=PORTB;
            else return(NOKAY);
            SET_BIT(RCGCGPIO,desired_port); // 1) activate clock for the specific port
            GPIO_enumSetPinDir(adc_groups[adc_confg[i].group_ID].ss_pins[j],INPUT);  // 2) make the desired pin input
            ADC_vidSetAlternateFunc(adc_groups[adc_confg[i].group_ID].ss_pins[j],desired_port); // 3) enable alternate function
            ADC_vidDisableDEN(adc_groups[adc_confg[i].group_ID].ss_pins[j],desired_port); //4) disable digital I/O
            ADC_vidEnAnalogFunc(adc_groups[adc_confg[i].group_ID].ss_pins[j],desired_port); // 5) enable analog function
        }
        RCGC0|=0x00010000; // 6)ACTIVATE ADC0

        RCGC0 &= ~(adc_confg[i].clk << 7); // 7) configure clk speed "8th and 9th bits"

        ADC0SSPRI=CONCBIT_SEQ(SAMPLE_SEQ3_PRI,SAMPLE_SEQ2_PRI,SAMPLE_SEQ1_PRI,SAMPLE_SEQ0_PRI); // 8) SET priority

        ADC_EnableDisableSeqSel(DISABLE,adc_confg[i].sequencer_no); // 9) disable sample sequencer which was chosen
        ADC_vidTrigger(adc_groups[adc_confg[i].group_ID].trigger,adc_confg[i].sequencer_no); // 10) SELECT THE trigger
        ADC_vidChannelSelection(adc_groups[adc_confg[i].group_ID].ss_pins,adc_confg[i].sequencer_no);// 11)Channel selection to sample
        ADC_vidSSCTL(adc_confg[i].sequencer_no,adc_confg[i].no_of_inp_channels); //12)Flag to be set & choose the end sample
        ADC_EnableDisableSeqSel(ENABLE,adc_confg[i].sequencer_no); // 13) enable sample sequencer which was chosen
    }
}
void ADC_Interrupt_Enable(u8 module_id)
{

    ADC0RIS=(1<<adc_confg[module_id].sequencer_no);
    SET_INT_PRI(adc_confg[module_id].sequencer_no+14,0);
    EN_INT(adc_confg[module_id].sequencer_no+14);
}
void ADC_vidStartConv(u8 module_id)
{
    if(adc_groups[adc_confg[module_id].group_ID].trigger ==SW) ADC0PSSI = 1 << (adc_confg[module_id].sequencer_no); // 1) initiate sample sequencer
    else if (adc_groups[adc_confg[module_id].group_ID].trigger==COMP0)
        {
            SET_BIT(ACCTL0,11); //Trigger Output Enable
            CLR_BIT(ACCTL0,9); //9:10 +ve source is the internal refrence
            SET_BIT(ACCTL0,10);
            SET_BIT(ACCTL0,7); //Trigger Sense Level Value -->1 ,An ADC event is generated if the comparator output is High.
        }
}
u32 DATA;
enumerr ADC_enumGetData(void)
{
    DATA = ADC0SSFIFO3&0xFFF;   // 3) read result
    ADC0ISC = 0x0008;             // 4) acknowledge completion
}

//enumerr (*ptrFunc)(void)=ADC_enumGetData;
void ADC_Sequence3_Handler(void)
{
  //  ptrFunc();
}


