/*
 * ADC_int.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_
#include "std_types.h"

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
/*Struct to hold the group information which has the same configuration mode*/
typedef struct{
    u8 group_ID;
    u8 conv_mode;
    u8 access_mode;
    u8 trigger;
    u8 HW_trigger_source;
    u8 ss_pins[MAX_CHANNELS_PER_GROUP];
}strGroupInfo;
/*Struct which holds a group for a specific module , and module refers to a sequencer*/
typedef struct
{
    u8 module_ID;
    u8 sequencer_no;
    u8 clk;
    u8 no_of_inp_channels;
    u8 group_ID;
}strModuleInfo;

/*Enum for error*/
typedef enum
{
    ADC_OKAY,
    ADC_NOTOKAY
}ADC_enumerr;

ADC_enumerr ADC_enuminit(void);
/*
 * Func: ADC_enuminit , it initiate the ADC with the configuration chosen at config.h file
 * Arguments: None.
 * Return :ADC_enumerr , to check if it's done or there's a problem
 * */
ADC_enumerr ADC_enumSetBuffer(u8 GP_ID, u32 * BufferPtr);
/*
 * Func: ADC_vidSetBuffer , it gives for a certain group its buffer pointer to hold the converted values.
 * Arguments: GP_ID and its buffer pointer.
 * Return :ADC_enumerr , to check if it's done or there's a problem
 * Note: it has to be called before the conversion
 * */
ADC_enumerr ADC_enumInterrupt_Enable(u8 module_id);
/*
 * Func: ADC_Interrupt_enable , it enables the interrupt for a specific module "sequencer"
 * Arguments: Module_id.
 * Return :ADC_enumerr , to check if it's done or there's a problem
 * */
void ADC_vidStartConv(u8 module_id);
/*
 * Func: ADC_vidStartConv , it starts the module conversion with the trigger chosen at config.h file
 * Arguments: Module_id.
 * Return :ADC_enumerr , to check if it's done or there's a problem
 * note: ADC_Interrupt_Enable has to be called first
 * */

void ADC_Sequence0_Handler(void);
void ADC_Sequence1_Handler(void);
void ADC_Sequence2_Handler(void);
void ADC_Sequence3_Handler(void);
/*
 * Func: ADC_SequenceN_Handler , they are the ISR for each sequencer , After each conversion it's called by default
 * Arguments: None.
 * Return :None
 * note: it can't be called by user
 * */
ADC_enumerr ADC_enumGetData(u8 gp_id);
/*
 * Func: ADC_enumGetData
 * Arguments: gp_id.
 * Return :ADC_enumerr , to check if it's done or there's a problem
 * P.S.:it's not supported for now
 * */

#endif /* ADC_INT_H_ */
