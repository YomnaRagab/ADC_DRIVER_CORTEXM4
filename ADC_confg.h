/*
 * ADC_confg.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_CONFG_H_
#define ADC_CONFG_H_

#include "ADC_int.h"

#define NUMOFGROUPS 1
#define NUMOFMODULES 1


strGroupInfo adc_groups[NUMOFGROUPS]={
                                      {0,CONV_ONE_SHOT,SINGLE_ACCESS,SW,NONE,{AIN0,'\0'}}
};
strModuleInfo adc_confg[NUMOFMODULES]={
                                           {0,SS3,SS_125k,1,0}
                                        };
// SAMPLE_SPEED SS_125k => 125k , 250k , 500k , 1M
#define SAMPLE_SEQ0_PRI 0
#define SAMPLE_SEQ1_PRI 1
#define SAMPLE_SEQ2_PRI 2
#define SAMPLE_SEQ3_PRI 3

#define ADC0_SS0_HANDLER_PRI           0
#define ADC0_SS1_HANDLER_PRI           0
#define ADC0_SS2_HANDLER_PRI           0
#define ADC0_SS3_HANDLER_PRI           0

//#define CONV_TRIGGER SW //SW CONT COMP0 TIMER

#endif /* ADC_CONFG_H_ */
