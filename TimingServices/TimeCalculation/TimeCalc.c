/*
 * TimeCalc.c
 *
 * Created: 11/21/2016 3:14:24 PM
 *  Author: AhmedShaarawy
 */ 


#include "TimeCalc.h"

volatile U32 TimerTurns=0;
U8 TimerTurnsOverFlowDetect=0x00;
U8 TimerID= 0x0A;
U16 TC0Capture;
U16 TC1Capture;
U16 TC2Capture;

STD_R StartTimer(U8 TimerId)
{
	StrartVerify();
	TC0_DeclareTimerObject();
	TC1_DeclareTimerObject();
	TC2_DeclareTimerObject();
	TimerID= TimerId;
	switch(TimerId)
	{
		case TC0ID:
			TC0_SetTimerNormalMode();
			TC0_EnableOVFInt();
			TC0_SetTimerPrescaleClk();
			TC0_Pass_IncremeteFn_ToOVFISR();
			TC0_CallYourInitFunction();
			break;
		case TC1ID:
			TC1_DisableOutPin();
			TC1_SetTimerNormalMode();
			TC1_EnableOVFInt();
			TC1_SetTimerPrescaleClk();
			TC1_Pass_IncremeteFn_ToOVFISR();
			TC1_CallYourInitFunction();
			break;
		case TC2ID:
			TC2_DisableOutPin();
			TC2_SetTimerNormalMode();
			TC2_EnableOVFInt();
			TC2_SetTimerPrescaleClk();
			TC2_Pass_IncremeteFn_ToOVFISR();
			TC2_CallYourInitFunction();
			break;
		default:
			TimerID= 0x0B;
			FalseVerify();
			break;
	}
	ReturnVerify();
}



STD_R GetTimerCounts( U32 *turns, U16 *capture)
{
	TC0Capture= TC0_CAPTURE_VALUE;
	TC1Capture= TC1_CAPTURE_VALUE;
	TC2Capture= TC2_CAPTURE_VALUE;
	*turns= TimerTurns;
	StrartVerify();
	if(!TimerTurnsOverFlowDetect)
	{
		switch(TimerID)
		{
			case TC0ID:
				*capture= TC0Capture;
				break;
			case TC1ID:
				*capture= TC1Capture;
				break;
			case TC2ID:
				*capture= TC2Capture;
				break;
			default:
				*turns= 0x00000000;
				*capture= 0x0000;
				FalseVerify();
				break;
		}
	}
	else
	{
		*turns= 0x00000000;
		*capture= 0x0000;
		TimerID= 0x0C;
		FalseVerify();
	}
	
	ReturnVerify();
}



STD_R StopTimer(void)
{
	StrartVerify();
	TimerTurnsOverFlowDetect= 0x00;
	switch(TimerID)
	{
		case TC0ID:
			TC0_StopTimer();
			TimerTurns= 0x00;
			TC0Capture= 0x00;
			break;
		case TC1ID:
			TC1_StopTimer();
			TimerTurns= 0x00;
			TC1Capture= 0x00;
			break;
		case TC2ID:
			TC2_StopTimer();
			TimerTurns= 0x00;
			TC2Capture= 0x00;
			break;
		default:
			FalseVerify();
			break;
	}
	
	ReturnVerify();
}



void IncrementFn(void)
{
	TimerTurns++;
	if (TimerTurns==0)
		TimerTurnsOverFlowDetect++;
}
