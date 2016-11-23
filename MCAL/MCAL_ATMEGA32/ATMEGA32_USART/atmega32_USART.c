/*
 * atmega32_UART.c
 *
 * Created: 10/3/2016 3:56:10 PM
 *  Author: AhmedShaarawy
 */ 

#include "atmega32_USART.h"
#define F_CPU 8000000ul

/******************************
** USART
*/


void (*PassTo_ISR_TXC)(void);
void (*PassTo_ISR_RXC)(void);
void (*PassTo_ISR_UDRE)(void);

U8 USARTInti(sUSART *ur)
{
	U8 check=0x00;
	U16 UBRR_val= 0x00;
	if (UR_TRUE_USART_OBJECT(ur->SyncAsyncMode,ur->XCKEdgeMode,ur->MPCMode,ur->DoubleSpeedMode,ur->IntModes,
							 ur->ParityCheckMode,ur->DataCharSize,ur->StopBitsNum,ur->TRxModes,ur->BuadRate )	)
	{
		check= 0x01;
		UCSRA &= ~((1<<MPCM)|(1<<U2X));
		UCSRB = 0x00;
		UCSRC = 0x80;
		UCSRA |= ur->MPCMode|ur->DoubleSpeedMode;
		UCSRB |= ur->IntModes|ur->TRxModes;
		UCSRC |= (1<<URSEL)|ur->ParityCheckMode|ur->StopBitsNum|ur->SyncAsyncMode;
		switch(ur->DataCharSize)
		{
			case UR_CHARSIZE_5: case UR_CHARSIZE_6: case UR_CHARSIZE_7: case UR_CHARSIZE_8:
				UCSRC |= ur->DataCharSize;									break;
			case UR_CHARSIZE_9:
				UCSRB |= 1<<UCSZ2;	UCSRC |= (1<<UCSZ0)|(1<<UCSZ1);			break;
		}
		ur->PassToTXCVector= PassTo_ISR_TXC;
		ur->PassToRXCVector= PassTo_ISR_RXC;
		ur->PassToUDREVector= PassTo_ISR_UDRE;
		// Baud Rate at UBRRL & UBRRH
		if( !READ_BIT(UCSRA,U2X) && !READ_BIT(UCSRC,UMSEL) )
			UBRR_val= ( ur->MCU_Freq/(16*ur->BuadRate) ) - 1 ;		// when Asynchronous and U2X is normal speed as = zero.
		else if( READ_BIT(UCSRA,U2X) && !READ_BIT(UCSRC,UMSEL) )
			UBRR_val= ( ur->MCU_Freq/(8*ur->BuadRate) ) - 1 ;		// when Asynchronous and U2X is double speed as = one.
		else if( READ_BIT(UCSRC,UMSEL) )
			UBRR_val= ( ur->MCU_Freq/(2*ur->BuadRate) ) - 1 ;		// when when Synchronous.
		UBRRL  = (U8)(UBRR_val & 0x00ff) ;							// write the first 8 low bits
		CLR_BIT(UBRRH,URSEL );										// select to write as UBRRH not UCSRC
		UBRRH |= (U8)(UBRR_val >> 8) ;								// write the last 8 high bits
	}
	return check;
}




U8 USARTTx(U16 data)
{
	U8 check= 0x00;
	if( data <= 0x01FF ) // if data within 9bits
	{
		check= 0x01;
		while ( !( UCSRA & (1<<UDRE)) );	// wait if there is an ongoing TRX.
		CLR_BIT(UCSRB,TXB8);				// clear TXB8 to send, if multi process core this bit must use bit
											// 0 to indicate data set to 1 to indicate address
		if( data & 0x0100)					// if the ninth bit is used and is 1, when MPCM and data is 8bit then you must use 2 stop bits.
			SET_BIT(UCSRB,TXB8);			// set the ninth bit to send.
		UDR= (U8)data;						// send data
	}
	return check;
}



U8 USARTRx(U16 *RxData)
{
	U8 check= 0x01;
	while ( !(UCSRA & (1<<RXC)) );				// wait for RX to be completed.
	if( UCSRA & ( 1<<PE | 1<<DOR | 1<<FE ) )	// if the status has an error
		check= 0x00;							// check = 0
	*RxData= UDR| ((READ_BIT(UCSRB,RXB8)<<8)) ;	// read the UDR with the ninth bit in UCSRB
	return check ;
}


ISR(USART_TXC_vect)
{
	PassTo_ISR_TXC();
}
ISR(USART_RXC_vect)
{
	PassTo_ISR_RXC();
}
ISR(USART_UDRE_vect)
{
	PassTo_ISR_UDRE();
}