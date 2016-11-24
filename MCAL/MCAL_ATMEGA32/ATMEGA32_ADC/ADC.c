/*
 * ADC.c
 *
 * Created: 11/24/2016 9:25:48 AM
 *  Author: AhmedShaarawy
 */ 


#include "ADC.h"

void (*PassToADC_ISR)(void);
U8 ADCInit( sADC *adc)
{
	U8 check= 0x00;
	if (ADC_TRUE_OBJECT(adc->Vref,adc->INTMode,adc->ResultAdjust,adc->TriggerMode,adc->Prescale,adc->AutoTriggerSource,adc->Channel))
	{
		check= 0x01;
		ADMUX   = 0;	ADCSRA  = 0;
		ADMUX  |= (adc->Vref<<REFS0)|(adc->Channel)|(adc->ResultAdjust<<ADLAR) ;
		ADCSRA |= (adc->TriggerMode<<ADATE)|(adc->Prescale)|(1<<ADEN);
		PassToADC_ISR= adc->pfPassToADCIntVect;
		if ( READ_BIT(ADCSRA,ADATE) )
			SFIOR |= adc->AutoTriggerSource<<ADTS0;
	}
	return check;
}


void ADCStart( void )
{
	SET_BIT(ADCSRA,ADSC);
}


void ADCRead( U16 *readVal )
{
	while( (ADCSRA&(1<<ADIF)) == 0 );
	*readVal  =  ADCL;
	*readVal |= (ADCH<<8);
}
