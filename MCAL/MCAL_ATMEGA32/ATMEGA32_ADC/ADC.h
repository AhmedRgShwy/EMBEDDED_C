/*
 * ADC.h
 *
 * Created: 11/24/2016 9:26:04 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "atmega32_IO.h"
#include <avr/interrupt.h>


#define ADC_VREF_INTERNAL_OFF	0x00
#define ADC_VREF_EXTERNAL_AVCC	0x01
#define ADC_VREF_INTERNAL_ON	0x03
#define ADC_TRUE_VREF(vr)		(vr>=0x00&&vr<=0x03)

#define ADC_INT_OFF	0x00
#define ADC_INT_ON	0x01
#define ADC_TRUE_INT(Int)		(Int==0x00||Int==0x01)

#define ADC_OUTPUT_LEFT_ADJUST	0x01
#define ADC_OUTPUT_RIGHT_ADJUST	0x00
#define ADC_TRUE_ADJUST(adj)	(adj==0x00||adj==0x01)

#define ADC_TRIGGER_SINGLE		0x00
#define ADC_TRIGGER_AUTO		0x01
#define ADC_TRUE_TRIGGER(trg)	(trg==0x00||trg==0x01)

#define ADC_PRESCALE_2			0x01
#define ADC_PRESCALE_4			0x02
#define ADC_PRESCALE_8			0x03
#define ADC_PRESCALE_16			0x04
#define ADC_PRESCALE_32			0x05
#define ADC_PRESCALE_64			0x06
#define ADC_PRESCALE_128		0x07
#define ADC_TRUE_SCALE(pre)		(pre>=0x00&&pre<=0x07)

#define ADC_AUTO_FREERUN		0x00
#define ADC_AUTO_ACMP			0x01
#define ADC_AUTO_EXTINT0		0x02
#define ADC_AUTO_TC0_CMP		0x03
#define ADC_AUTO_TC0_OVF		0x04
#define ADC_AUTO_TC1_CMPB		0x05
#define ADC_AUTO_TC1_OVF		0x06
#define ADC_AUTO_TC1_CAP		0x07
#define ADC_TRUE_SOURCE(src)	(src>=0x00&&src<=0x07)	


typedef enum{
	singleADC0=0,
	singleADC1=1,
	singleADC2=2,
	singleADC3=3,
	singleADC4=4,
	singleADC5=5,
	singleADC6=6,
	singleADC7=7,
	cmpADC0_ADC0ref_Gain10=8,
	cmpADC1_ADC0ref_Gain10=9,
	cmpADC0_ADC0ref_Gain200=10,
	cmpADC1_ADC0ref_Gain200=11,
	cmpADC2_ADC2ref_Gain10=12,
	cmpADC3_ADC2ref_Gain10=13,
	cmpADC2_ADC2ref_Gain200=14,
	cmpADC3_ADC2ref_Gain200=15,
	cmpADC0_ADC1ref=16,
	cmpADC1_ADC1ref=17,
	cmpADC2_ADC1ref=18,
	cmpADC3_ADC1ref=19,
	cmpADC4_ADC1ref=20,
	cmpADC5_ADC1ref=21,
	cmpADC6_ADC1ref=22,
	cmpADC7_ADC1ref=23,
	cmpADC0_ADC2ref=24,
	cmpADC1_ADC2ref=25,
	cmpADC2_ADC2ref=26,
	cmpADC3_ADC2ref=27,
	cmpADC4_ADC2ref=28,
	cmpADC5_ADC2ref=29,
	singleVBG122V=30,
	singleGND0V=31
} eChannelGain_Sel;
#define ADC_TRUE_CHANNEL(cha)					(cha>=0x00&&cha<=0x31)
#define ADC_TRUE_OJBECT(vr,Int,adj,trg,pre,src,cha)		ADC_TRUE_VREF(vr)&&ADC_TRUE_INT(Int)&&ADC_TRUE_ADJUST(adj)&&ADC_TRUE_CHANNEL(cha)&&\
								ADC_TRUE_TRIGGER(trg)&&ADC_TRUE_SCALE(pre)&&ADC_TRUE_SOURCE(src)

#define DisableADC()	CLR_BIT(ADCSRA,ADEN)
#define DisableADCInt()	CLR_BIT(ADCSRA,ADIE)

typedef struct
{
	U8					Vref;
	U8					ResultAdjust;
	U8					Prescale;
	U8					TriggerMode;
	U8					AutoTriggerSource;
	U8					INTMode;
	eChannelGain_Sel	Channel;
	void (*pfPassToADCIntVect)(void);
} sADC;

U8 ADCInit( sADC *adc);
void ADCStart( void );
void ADCRead( U16 *readVal );


#endif /* ADC_H_ */
