/*
 * main.c
 *
 *  Created on: Oct 28, 2019
 *      Author: Yomna Ragab
 */
#include <ADC_memory_map.h>
#include "std_types.h"
#include "GPIO_Priv.h"
#include "GPIO_Mem_Map.h"
#include "GPIO_Int.h"
#include "ADC_memory_map.h"
extern u32 PORTS_BASES[PORTS_NUMBER];
void main (void)
{
    GPIO_Init();

    GPIO_enumSetPinDir(PORTE_PIN2,INPUT);//    Step 1. We enable the port clock for the pin that we will be using for the ADC input.

                                              //    Step 2. Make that pin an input by writing zero to the DIR register.

         GPIOAFSEL(PORTE) |=0x04;               //    Step 3. Enable the alternative function on that pin by writing one to the AFSEL register.

         GPIODEN(PORTE) &= ~0x04;                 //    Step 4. Disable the digital function on that pin by writing zero to the DEN register.

         GPIOAMSEL(PORTE)|=0x04;              //    Step 5. Enable the analog function on that pin by writing one to the AMSEL register.

       //  RCGCADC |=0x01;                       //    Step 6. We enable the ADC clock by setting bit 16 of the SYSCTL_RCGC0_R register.
         RCGC0|=0x00010000;
         RCGC0 &= ~0x00000300;                   //    Step 7. Bits 8 and 9 of the SYSCTL_RCGC0_R register specify the maximum sampling rate of the ADC. In this example, we will sample slower than 125 kHz, so the maximum sampling rate is set at 125 kHz. This will require less power and produce a longer sampling time, creating a more accurate conversion.

         ADC0SSPRI =0x0123;        //    Step 8. We will set the priority of each of the four sequencers. In this case, we are using just one sequencer, so the priorities are irrelevant, except for the fact that no two sequencers should have the same priority.

         ADC0ACTSS &= ~0x0008;       //    Step 9. Before configuring the sequencer, we need to disable it. To disable sequencer 3, we write a 0 to bit 3 (ASEN3) in the ADC_ACTSS_R register. Disabling the sequencer during programming prevents erroneous execution if a trigger event were to occur during the configuration process.

         ADC0EMUX &= ~0xF000;     //    Step 10. We configure the trigger event for the sample sequencer in the ADC_EMUX_R register. For this example, we write a 0000 to bits 15–12 (EM3) specifying software start mode for sequencer 3.

         ADC0SSMUX3=0x01; //Step 11. Configure the corresponding input source in the ADCSSMUXn register. In this example, we write the channel number to bits 3–0 in the ADC_SSMUX3_R register. In this example, we sample channel 9, which is PE4.
    //
         ADC0SSCTL3=0x006;//    Step 12. Configure the sample control bits in the corresponding nibble in the ADC0SSCTLn register. When programming the last nibble, ensure that the END bit is set. Failure to set the END bit causes unpredictable behavior. Sequencer 3 has only one sample, so we write a 0110 to the ADC_SSCTL3_R register. Bit 3 is the TS0 bit, which we clear because we are not measuring temperature. Bit 2 is the IE0 bit, which we set because we want to the RIS bit to be set when the sample is complete. Bit 1 is the END0 bit, which is set because this is the last (and only) sample in the sequence. Bit 0 is the D0 bit, which we clear because we do not wish to use differential mode.
    //
         ADC0ACTSS |= 0x0008;//    Step 13. We enable the sample sequencer logic by writing a 1 to the corresponding ASENn. To enable sequencer 3, we write a 1 to bit 3 (ASEN3) in the ADC_ACTSS_R register.
    ///////////////////////////////////////////////////////////////////////////////////////////////
         u32 result;
         while (1)
            {



     ADC0PSSI = 0x0008;            // 1) initiate SS3

       while((ADC0RIS&0x08)==0){};   // 2) wait for conversion done

       result = (ADC0SSFIFO3&0xFFF)*100000;   // 3) read result

       ADC0ISC = 0x0008;             // 4) acknowledge completion
        if ((result > 400000000) && (result < 408100000) ) GPIO_enumSetPortVal(PORTF,0x02);
        else if ((result > 408100005) &&( result <408200000)) GPIO_enumSetPortVal(PORTF,0x04);
        else if (result > 408200005) GPIO_enumSetPortVal(PORTF,0x08);
        volatile u32 i=0;
        for (i=0; i<9999; i++)
        {

        }

}
}



