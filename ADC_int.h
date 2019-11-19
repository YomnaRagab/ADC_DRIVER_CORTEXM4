/*
 * ADC_int.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_
#define AIN0  0
#define AIN1  1
#define AIN2  2
#define AIN3  3
#define AIN4  4
#define AIN5  5
#define AIN6  6
#define AIN7  7
#define AIN8  8
#define AIN9  9
#define AIN10 10
#define AIN11 11

#define SS3 3
#define SS2 2
#define SS1 1
#define SS0 0

#define MAX_CHANNELS_PER_GROUP 8
typedef struct
{
    u8 group_ID;
    u8 conv_mode;
    u8 access_mode;
    u8 trigger;
    u8 HW_trigger_source;
    u8 ss_pins[MAX_CHANNELS_PER_GROUP];
}strGroupInfo;

typedef struct
{
    u8 module_ID;
    u8 sequencer_no;
    u8 clk;
    u8 no_of_inp_channels;
    u8 group_ID;
}strModuleInfo;
//#define AIN0  PORTE_PIN3
//#define AIN1  PORTE_PIN2
//#define AIN2  PORTE_PIN1
//#define AIN3  PORTE_PIN0
//#define AIN4  PORTD_PIN3
//#define AIN5  PORTD_PIN2
//#define AIN6  PORTD_PIN1
//#define AIN7  PORTD_PIN0
//#define AIN8  PORTE_PIN5
//#define AIN9  PORTE_PIN4
//#define AIN10 PORTB_PIN4
//#define AIN11 PORTB_PIN5
enumerr ADC_enuminit(void);
void ADC_Interrupt_Enable(u8 module_id);
void ADC_vidStartConv(u8 module_id);
enumerr ADC_enumGetData(void);
void ADC_Sequence0_Handler(void);
void ADC_Sequence1_Handler(void);
void ADC_Sequence2_Handler(void);
void ADC_Sequence3_Handler(void);


#endif /* ADC_INT_H_ */
