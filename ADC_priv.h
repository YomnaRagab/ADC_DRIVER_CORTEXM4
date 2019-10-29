/*
 * ADC_priv.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_
#define SS_125k 0x0
#define SS_250k 0x1
#define SS_500k 0x2
#define SS_1M 0x3

#define ENABLE 1
#define DISABLE 0

#define SS3 3
#define SS2 2
#define SS1 1
#define SS0 0

#define SW 0
#define CONT 1
#define COMP0 2
void ADC_vidSetAlternateFunc(u8 pin,u8 desired_port);
void ADC_vidDisableDEN(u8 pin,u8 desired_port);
void ADC_vidEnAnalogFunc(u8 pin,u8 desired_port);
void ADC_vidSampleSpeed(void);
void ADC_SeqSelPriority(void);
void ADC_EnableDisableSeqSel(u8 control);
void ADC_vidTrigger(void);
void ADC_vidChannelSelection(u8 pin);
#endif /* ADC_PRIV_H_ */
