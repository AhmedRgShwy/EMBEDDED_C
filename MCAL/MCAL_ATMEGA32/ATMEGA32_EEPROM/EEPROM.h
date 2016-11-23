/*
 * EEPROM.h
 *
 * Created: 11/23/2016 5:09:57 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "atmega32_lib.h"
#include <avr/interrupt.h>

#define DisableEEPROMInt()		CLR_BIT(EECR,EERIE);

U8 EEPROMWriteByte(U8 data, U16 address);
U8 EEPROMReadByte(U16 address, U8 *ReadData);
void EEPROMIntInit(void(*PassToEEPROMIntRedyVector)(void));

#endif /* EEPROM_H_ */