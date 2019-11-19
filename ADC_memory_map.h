/*
 * adc_memory_map.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Yomna Ragab
 */

#ifndef ADC_MEMORY_MAP_H_
#define ADC_MEMORY_MAP_H_
/*ADC BASIS*/
#define ADC0_BASE            0x40038000
#define ADC1_BASE            0x40039000
/*ADC CLK*/
#define RCGCADC_OFFSET       0x638
#define RCGCADC_BASE         0x400FE000
#define RCGCADC              *((volatile u32*)(RCGCADC_BASE+RCGCADC_OFFSET))
/*Run Mode Clock Gating Control Register 0*/
#define RCGC0_BASE          0x400FE000
#define RCGC0_OFFSET        0x100
#define RCGC0               *((volatile u32*)(RCGC0_BASE+RCGC0_OFFSET))
/*ADC Sample Sequencer Priority */
#define ADCSSPRI_OFFSET     0x020
#define ADC0SSPRI           *((volatile u32*)(ADC0_BASE+ADCSSPRI_OFFSET))
#define ADC1SSPRI           *((volatile u32*)(ADC1_BASE+ADCSSPRI_OFFSET))
/*ADC Active Sample Sequencer*/
#define ADCACTSS_OFFSET     0x000
#define ADC0ACTSS           *((volatile u32*)(ADC0_BASE+ADCACTSS_OFFSET))
#define ADC1ACTSS           *((volatile u32*)(ADC1_BASE+ADCACTSS_OFFSET))
/*ADC Event Multiplexer Select*/
#define ADCEMUX_OFFSET      0x014
#define ADC0EMUX            *((volatile u32*)(ADC0_BASE+ADCEMUX_OFFSET))
#define ADC1EMUX            *((volatile u32*)(ADC1_BASE+ADCEMUX_OFFSET))
/*ADC Sample Sequence Input Multiplexer Select 3*/
#define ADCSSMUX3_OFFSET      0x0A0
#define ADC0SSMUX3            *((volatile u32*)(ADC0_BASE+ADCSSMUX3_OFFSET))
#define ADC1SSMUX3            *((volatile u32*)(ADC1_BASE+ADCSSMUX3_OFFSET))
/*ADC Sample Sequence Input Multiplexer Select 2 */
#define ADCSSMUX2_OFFSET      0x080
#define ADC0SSMUX2            *((volatile u32*)(ADC0_BASE+ADCSSMUX2_OFFSET))
/*ADC Sample Sequence Input Multiplexer Select 1 */
#define ADCSSMUX1_OFFSET      0x060
#define ADC0SSMUX1            *((volatile u32*)(ADC0_BASE+ADCSSMUX1_OFFSET))
/*ADC Sample Sequence Input Multiplexer Select 0*/
#define ADCSSMUX0_OFFSET       0x040
#define ADC0SSMUX0            *((volatile u32*)(ADC0_BASE+ADCSSMUX0_OFFSET))
/*ADC Sample Sequence Control 3*/
#define ADCSSCTL3_OFFSET      0x0A4
#define ADC0SSCTL3            *((volatile u32*)(ADC0_BASE+ADCSSCTL3_OFFSET))
#define ADC1SSCTL3            *((volatile u32*)(ADC1_BASE+ADCSSCTL3_OFFSET))
/*ADC Sample Sequence Control 0*/
#define ADCSSCTL0_OFFSET         0x044
#define ADC0SSCTL0            *((volatile u32*)(ADC0_BASE+ADCSSCTL0_OFFSET))
#define ADC1SSCTL0            *((volatile u32*)(ADC1_BASE+ADCSSCTL0_OFFSET))
/*ADC Sample Sequence Control 1*/
#define ADCSSCTL1_OFFSET        0x064
#define ADC0SSCTL1            *((volatile u32*)(ADC0_BASE+ADCSSCTL1_OFFSET))
#define ADC1SSCTL1            *((volatile u32*)(ADC1_BASE+ADCSSCTL1_OFFSET))
/*ADC Sample Sequence Control 2*/
#define ADCSSCTL2_OFFSET         0x084
#define ADC0SSCTL2            *((volatile u32*)(ADC0_BASE+ADCSSCTL2_OFFSET))
#define ADC1SSCTL2            *((volatile u32*)(ADC1_BASE+ADCSSCTL2_OFFSET))
/*ADC Sample Sequence Input Multiplexer Select 0 */
#define ADCSSMUX0_OFFSET    0x040
#define ADC0SSMUX0            *((volatile u32*)(ADC0_BASE+ADCSSMUX0_OFFSET))
#define ADC1SSMUX0            *((volatile u32*)(ADC1_BASE+ADCSSMUX0_OFFSET))
/*ADC Processor Sample Sequence Initiate*/
#define ADCPSSI_OFFSET        0x028
#define ADC0PSSI            *((volatile u32*)(ADC0_BASE+ADCPSSI_OFFSET))
#define ADC1PSSI            *((volatile u32*)(ADC1_BASE+ADCPSSI_OFFSET))
/*ADC Raw Interrupt Status*/
#define ADCRIS_OFFSET       0x004
#define ADC0RIS            *((volatile u32*)(ADC0_BASE+ADCRIS_OFFSET))
#define ADC1RIS            *((volatile u32*)(ADC1_BASE+ADCRIS_OFFSET))
/*ADC Sample Sequence Result FIFO 3*/
#define ADCSSFIFO3_OFFSET    0x0A8
#define ADC0SSFIFO3            *((volatile u32*)(ADC0_BASE+ADCSSFIFO3_OFFSET))
#define ADC1SSFIFO3            *((volatile u32*)(ADC1_BASE+ADCSSFIFO3_OFFSET))
/*ADC Interrupt Status and Clear*/
#define ADCISC_OFFSET       0x00C
#define ADC0ISC           *((volatile u32*)(ADC0_BASE+ADCISC_OFFSET))
#define ADC1ISC           *((volatile u32*)(ADC1_BASE+ADCISC_OFFSET))
/*Analog Comparator Control 0*/
#define ACCTL0_OFFSET    0x024
#define ACCTL0_BASE      0x4003C000
#define ACCTL0           *((volatile u32*)(ACCTL0_BASE+ACCTL0_OFFSET))
/*ADC Interrupt Mask*/
#define ADCIM_OFFSET     0x008
#define ADC0IM           *((volatile u32*)(ADC0_BASE+ADCIM_OFFSET))
#define ADC1IM           *((volatile u32*)(ADC1_BASE+ADCIM_OFFSET))
/*Interrupt Enable */
#define INTERRUPT_BASE  0xE000E000
#define EN_REG_BASE 0x100
#define EN_REG_NUM(INT_NUM) (INT_NUM/32) //to jump one reg after 32 interrupt according to datasheet
#define EN_REG(INT_NUM) *((u32)((EN_REG_NUM(INT_NUM) * 4) + EN_REG_BASE + INTERRUPT_BASE))
#define EN_INT(INT_NUM)  EN_REG(INT_NUM) |= (1 << ((INT_NUM) % 32))
/*Interrupt priority*/
#define PRI_REG_BASE 0x400
#define PRI_REG_NUM(INT_NUM) (INT_NUM/4) //to get n which refers to PRIn and jump one reg after 4 n
#define PRI_REG(INT_NUM) *((u32)((PRI_REG_NUM(INT_NUM) * 4) + PRI_REG_BASE + INTERRUPT_BASE))//addition of any number divided by 4
#define SET_INT_PRI(INT_NUM,PRI_NUM) PRI_REG(INT_NUM) &= ~(0x0F <<  (8*(INT_NUM%4)+5) );\ //clear
                                     PRI_REG(INT_NUM) |= ((PRI_NUM & 0X0F)<< (8*(INT_NUM%4)+5)) // set INTA/B/C/D shifting by the remaining multiplied by 8 (to jump form 5th bit to 13th bit) added to 5
#endif /* ADC_MEMORY_MAP_H_ */
