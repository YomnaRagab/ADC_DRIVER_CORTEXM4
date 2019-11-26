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
#include "GPIO_Utils.h"
#include "ADC_memory_map.h"
#include "ADC_int.h"
#include "ADC_priv.h"
#include "ADC_confg.h"

extern u32 PORTS_BASES[PORTS_NUMBER];
extern strGroupInfo adc_groups[NUMOFGROUPS];
extern strModuleInfo adc_confg[NUMOFMODULES];
u32* Adc_resultBuffer[8];
/*array of pointer to hold a buffer pointer for each gp*/
u8 finished_samples[8]={0};
/*no of finished samples for each gp*/
u32 ADC_FIFOn[]={ADCSSFIFO0_OFFSET,ADCSSFIFO1_OFFSET,ADCSSFIFO2_OFFSET,ADCSSFIFO3_OFFSET};
/*FIFO registers offset*/
u32 ADC_SSCTLn[]={ADCSSCTL0_OFFSET,ADCSSCTL1_OFFSET,ADCSSCTL2_OFFSET,ADCSSCTL3_OFFSET};
/*SSCTL registers offset*/
u32 ADC_SSMUXn[]={ADCSSMUX0_OFFSET,ADCSSMUX1_OFFSET,ADCSSMUX2_OFFSET,ADCSSMUX3_OFFSET};
/*SSMUX registers offset*/
ADC_enumerr ADC_enuminit(void)
{
    u8 i,j,desired_port;
    for (i=0; i<NUMOFMODULES; i++)
    {
        for (j=0; j<adc_confg[i].no_of_inp_channels; j++) //setup pins to be ADC
        {
            if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN0) || (adc_groups[adc_confg[i].group_ID].ss_pins[j]== AIN1) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN2) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN3) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN8) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN9)) desired_port=PORTE;
            else if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN4) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN5) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN6) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN7)) desired_port=PORTD;
            else if ((adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN10) || (adc_groups[adc_confg[i].group_ID].ss_pins[j] == AIN11) ) desired_port=PORTB;
            else return(ADC_NOTOKAY);
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
    return(ADC_OKAY);
}
ADC_enumerr ADC_enumInterrupt_Enable(u8 module_id)
{

    ADC0IM=(1<<adc_confg[module_id].sequencer_no);
    /*Enable the interrupt mask of the module*/
    SET_INT_PRI((adc_confg[module_id].sequencer_no)+14,0);
    /*Set the interrupt priority by calling set interrupt priority and give it the SS no added to 14 to
     * matched the number in the interrupt vector table, and 0 it's priority*/
    EN_INT(adc_confg[module_id].sequencer_no+14);
    /**
     * Enable the interrupt by giving the macors func the interrupt no in the vector table
     */
    return(ADC_OKAY);
}
void ADC_vidStartConv(u8 module_id)
{
    if(adc_groups[adc_confg[module_id].group_ID].trigger ==SW) ADC0PSSI = 1 << (adc_confg[module_id].sequencer_no);
    /*initiate the sample sequencer by software by writing 1 on the PSSI reg shifted by the sequencer number*/
    else if (adc_groups[adc_confg[module_id].group_ID].trigger==COMP0)
    {
        SET_BIT(ACCTL0,11); //Trigger Output Enable
        CLR_BIT(ACCTL0,9); //9:10 +ve source is the internal refrence
        SET_BIT(ACCTL0,10);
        SET_BIT(ACCTL0,7); //Trigger Sense Level Value -->1 ,An ADC event is generated if the comparator output is High.
    }
    /*
     * this mode is not completed yet
     */
}
ADC_enumerr ADC_enumSetBuffer(u8 GP_ID, u32 * BufferPtr)
{
    Adc_resultBuffer[GP_ID]=BufferPtr;
    /*set the buffer pointer for each gp*/
    return(ADC_OKAY);
}

ADC_enumerr ADC_enumGetData(u8 gp_id)
{

    return (ADC_OKAY);
}

void ADC_Sequence3_Handler(void)
{
    u8 noOfChannels=adc_confg[0].no_of_inp_channels;
    u8 gp_id=adc_confg[0].group_ID;
    u8 i=0;
    for (i=finished_samples[gp_id]; i<((noOfChannels*(finished_samples[gp_id])+1)); i++)
    {
        *(Adc_resultBuffer[gp_id]+i)=ADC0_SSFIFO(SS3);
        /*
         *put the converted result on the buffer and each time started from the finished samples*no of channels to
         *avoid overwriting data
          */
    }
    finished_samples[gp_id]++;
    SET_ISC(SS3);
    /*Sent an acknowledge by set the interrupt and status for ss3*/
    if(finished_samples[gp_id]==noOfChannels)  finished_samples[gp_id]=0;
}
void ADC_Sequence2_Handler(void)
{
    u8 noOfChannels=adc_confg[1].no_of_inp_channels;
    u8 gp_id=adc_confg[1].group_ID;
    u8 i=0;
    for (i=finished_samples[gp_id]; i<((noOfChannels*(finished_samples[gp_id])+1)); i++)
    {
        *(Adc_resultBuffer[gp_id]+i)=ADC0_SSFIFO(SS2);
    }
    finished_samples[gp_id]++;
    SET_ISC(SS2);
    /*Sent an acknowledge by set the interrupt and status for ss2*/
    if(finished_samples[gp_id]==noOfChannels)  finished_samples[gp_id]=0;
}
void ADC_Sequence1_Handler(void)
{
    u8 noOfChannels=adc_confg[2].no_of_inp_channels;
    u8 gp_id=adc_confg[2].group_ID;
    u8 i=0;
    for (i=finished_samples[gp_id]; i<((noOfChannels*(finished_samples[gp_id])+1)); i++)
    {
        *(Adc_resultBuffer[gp_id]+i)=ADC0_SSFIFO(SS1);
    }
    finished_samples[gp_id]++;
    SET_ISC(SS1);
    /*Sent an acknowledge by set the interrupt and status for ss1*/
    if(finished_samples[gp_id]==noOfChannels)  finished_samples[gp_id]=0;
}
void ADC_Sequence0_Handler(void)
{
    u8 noOfChannels=adc_confg[3].no_of_inp_channels;
        u8 gp_id=adc_confg[3].group_ID;
        u8 i=0;
        for (i=finished_samples[gp_id]*noOfChannels; i<((noOfChannels*(finished_samples[gp_id])+1)); i++)
        {
            *(Adc_resultBuffer[gp_id]+i)=ADC0_SSFIFO(SS0);
        }
        finished_samples[gp_id]++;
        SET_ISC(SS0);
        /*Sent an acknowledge by set the interrupt and status for ss0*/
        if(finished_samples[gp_id]==noOfChannels)  finished_samples[gp_id]=0;
}


