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
enumerr ADC_enumSetPin(u8 pin); //AIN0 to AIN11
enumerr ADC_enumGetData(u16* Data);



#endif /* ADC_INT_H_ */
