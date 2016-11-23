/*
 * atmega32_I2C.c
 *
 * Created: 10/4/2016 2:04:37 PM
 *  Author: AhmedShaarawy
 */ 

#define F_CPU 8000000ul
#include "atmega32_TWI.h"


void (*pfTWIISRExecute)(void);
U8 TWIInit(sTWI *twi)
{
	U8	check= 0x00;
	if(TWI_TRUE_OBJECT(twi->Prescale,twi->IntMode,twi->GCallMode,twi->Addr)) // check argument verification
	{
		check= 1;
		TWBR  = (twi->MCU_CLK-16*twi->SCL_Freq)/(2*twi->SCL_Freq*twi->Prescale);		// equation baud-rate setting
		TWCR |= (1<<TWEA)|(1<<TWEN);	 // enable Acknowledge & enable TWI module, if it cleared TWI will be virtually disconnected till it set.
		TWCR &= ~( (1<<TWSTO)|(1<<TWSTA) );
		TWCR |= twi->IntMode;
		pfTWIISRExecute= twi->pfTWIIntVector;
		TWAR |= twi->GCallMode;
		TWSR |= twi->Prescale;
	}
	return check;
}



void TWITxByte(U8 byte)
{
	while( !READ_BIT(TWCR,TWINT) );		// wait for complete previous progress
	TWDR= byte;
	TWITriggerTx();
}



void TWIRxByte(U8 *RxByte)
{
	while( !READ_BIT(TWCR,TWINT) );		// wait for complete previous progress
	*RxByte= TWDR ;
}




ISR(TWI_vect)
{
	pfTWIISRExecute();
}