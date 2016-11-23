/*
 * atmega32_I2C.h
 *
 * Created: 10/4/2016 2:05:10 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef ATMEGA32_TWI_H_
#define ATMEGA32_TWI_H_
#include "atmega32_IO.h"
#include <avr/interrupt.h>


/******************* ( section 0 ) ************************************************
** TWI PRESCALE, GENERAL CALL, TWI mode AND INTERRUPT
*/
#define TWI_PRESCALE_1		0x00
#define TWI_PRESCALE_4		0x01
#define TWI_PRESCALE_16		0x02
#define TWI_PRESCALE_64		0x03
#define TWI_TRUE_PRESCALE(pre)		(pre>=0&&pre<=3)

#define TWI_INT_ENABLE		0x01
#define TWI_INT_DISABLE		0x00
#define TWI_TRUE_INT(Int)			(Int==0||Int==1)

#define TWI_GCALL_DISABLE	0x00
#define TWI_GCALL_ENABLE	0x01
#define TWI_TRUE_GCALL(gc)			(gc==0||gc==1)
#define TWI_TRUE_ADDRESS(addr)		(addr>0x00&&addr<0x78)
#define TWI_TRUE_OBJECT(pre,Int,gc,addr)	TWI_TRUE_PRESCALE(pre)&&TWI_TRUE_INT(Int)&&\
											TWI_TRUE_GCALL(gc)&&TWI_TRUE_ADDRESS(addr)
/**********************************************************************************
*/



/******************* ( section 1 ) ************************************************
** TWI MASTER TRANSMITE STATUS
*/
#define TWIMT_START_SENT		0x08
#define TWIMT_RSTART_SENT		0x10
#define TWIMT_SLAWT_ACKR		0x18
#define TWIMT_SLAWT_NACKR		0x20
#define TWIMT_DATAT_ACKR		0x28
#define TWIMT_DATAT_NACKR		0x30
#define TWIMT_ARBTLOST			0x38
/************************************************************************************
*/


/******************* ( section 2 ) **************************************************
** TWI MASTER RECEIVE STATUS
*/
#define TWIMR_START_SENT			0x08
#define TWIMR_RSTART_SENT			0x10
#define TWIMR_ARBTLOST_OR_NACKR		0x38
#define TWIMR_SLART_ACKR			0x40
#define TWIMR_SLART_NACKR			0x48
#define TWIMR_DATAR_ACKT			0x50
#define TWIMR_DATAR_NACKT			0x58
/*************************************************************************************
*/


/******************** ( section 3 ) ***************************************************
** TWI SLAVE RECEIVE STATUS
** ACKS == ACK Sent, NACKS == Not ACK Sent
*/
#define TWISR_OWNSLAW_ACKT				0x60
#define TWISR_ARBTLOST_OWNADDR_ACKT		0x68
#define TWISR_ADDR_GCALLR_ACKT			0x70
#define TWISR_ARBTLOST_GCALL_ACKT		0x78
#define TWISR_DATAR_OWNADDR_ACKT		0x80
#define TWISR_DATAR_OWNADDR_NACKT		0x88
#define TWISR_DATA_GCALLR_ACKT			0x90
#define TWISR_DATA_GCALLR_NACKT			0x98
#define TWISR_STOPR_OR_RSTARTR			0xA0
/**************************************************************************************
*/


/******************** ( section 4 ) ****************************************************
** TWI SLAVE TRANSMITE STATUS
** ACKT == ACK Transmitted, NACKT == Not ACK Transmitted
** DATAT == Data Transmitted
*/
#define TWIST_OWNSLAR_ACKT				0xA8
#define TWIST_ARBTLOST_OWNADDR_ACKT		0xB0
#define TWIST_DATAT_ACKR				0xB8
#define TWIST_DATAT_NACKR				0xC0
#define TWIST_LASTDATAT_ACKR			0xC8
/****************************************************************************************
*/


/******************** ( section 5 ) ****************************************************
** MISCELLENOUS STATUS
*/
#define TWI_NOSTATINFO_AVAILABLE			0xF8  // TWINT == 0
#define TWI_BUSERROR_ILLEGAL_STARTSTOP		0x00
/*****************************************************************************************
*/


/******************** ( section 7 ) *****************************************************
** Check status and collision
*/
#define TWI_READ_INTFLAG			READ_BIT(TWCR,TWINT)
#define TWI_READ_STATUS				TWSR&0xF8
// return true if status happen, false otherwise.
#define TWI_CHECK_STATUS(Status)	((TWI_READ_STATUS) == Status)
// use to check collision flag
#define TWI_CHECK_COLLISION			READ_BIT(TWCR,TWWC)
/*****************************************************************************************
*/


/******************** ( section 8 ) ******************************************************
** Start and stop generation
*/
// use this MAKRO to generate start condition and start the transmission as a master.
#define TWIStartCondition()			TWCR|= (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);\
									while(( TWCR&(1<<TWINT))== 0 )
// use this MAKRO to generate stop condition and ended the transmission when master.
#define TWIStopCondition()			TWCR|= (1<<TWEN)|(1<<TWINT)|(1<<TWSTO)
/*****************************************************************************************
*/

/******************** ( section 9 ) ******************************************************
** Trigger transmit and make virtual connection
*/
// After writing to the TWDR register, trigger to start transmit.
#define TWITriggerTx()				TWCR|= (1<<TWEN)|(1<<TWINT)
// use this MAKRO to be virtually disconnected.from the bus.
#define TWIVirtualDisconnectMode()		CLR_BIT(TWCR,TWEA)
// to start critical section against TWI interrupt
#define TWIStartCritical()				CLR_BIT(TWCR,TWIE)
// to end the TWI critical section
#define TWIEndCritical()				SET_BIT(TWCR,TWIE)
#define TWIEnableInt()					SET_BIT(TWCR,TWIE)
#define TWIDisableInt()					CLR_BIT(TWCR,TWIE)
/******************************************************************************************
*/

/******************** ( section 10 ) ******************************************************
** Set an address as read or write
*/
// use to mas the address with write 
#define TWIMASKSLAW(address)			(address&=~0x01)		// set the least by zero
// use to mask the address with read
#define TWIMASKSLAR(address)			(address|=0x01)			// set the least by one
/******************************************************************************************
*/

/********************* ( section 11 ) *****************************************************
** INITIATION STRUCTURE
*/

typedef struct  
{
	U8 Prescale;					// CLK PRESCALE.
	U8 Addr;						// address to be set when used as slave.
	U8 IntMode;						// enable or disable interrupt
	U8 GCallMode;					// disable or enable general call.
	U32 MCU_CLK;					// MCU CLK => F_CPU.
	U32 SCL_Freq;					// desired frequency.
	void (*pfTWIIntVector)(void);
	}sTWI;							// shortcut s in sTWI notice you as structure.
/*****************************************************************************************
*/


/********************* ( section 12 ) *****************************************************
** TWI FUNCTIONS
*/
// initialize Baud, speed, interrupt, Acknowledge, address
U8 TWIInit(sTWI *i2c);
// send a byte, may be data or address( SLAW or SLAR )
void TWITxByte(U8 byte);
// byte always data not address.
void TWIRxByte(U8 *RxByte);
/*****************************************************************************************
*/





#endif /* ATMEGA32_TWI_H_ */