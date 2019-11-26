/*
 * ADC_priv.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

#define ADC0_SEQ0_INT_NO 14
#define ADC0_SEQ1_INT_NO 15
#define ADC0_SEQ2_INT_NO 16
#define ADC0_SEQ3_INT_NO 17

#define SS_125k 0x3
#define SS_250k 0x2
#define SS_500k 0x1
#define SS_1M 0x0

#define ENABLE 1
#define DISABLE 0


#define CONV_ONE_SHOT 0
#define CONV_CONT_SHOT 1

#define STREAMING_ACCESS 0
#define SINGLE_ACCESS 1

#define NONE 99

#define SW 0
#define CONT 1
#define COMP0 2
#define TIMER 3
void ADC_vidSetAlternateFunc(u8 pin,u8 desired_port);
void ADC_vidDisableDEN(u8 pin,u8 desired_port);
void ADC_vidEnAnalogFunc(u8 pin,u8 desired_port);
void ADC_EnableDisableSeqSel(u8 control,u8 sample_seq);
void ADC_vidTrigger(u8,u8);
void ADC_vidChannelSelection(u8 *pin, u8 sample_seq);
void ADC_vidSSCTL(u8 seq,u8 no_of_channels);
#define CONCBIT_SEQ(P3,P2,P1,P0) CONCBIT_HELPER_SEQ(P3,P2,P1,P0)
#define CONCBIT_HELPER_SEQ(P3,P2,P1,P0)  (0x##P3##P2##P1##P0)
#endif /* ADC_PRIV_H_ */
