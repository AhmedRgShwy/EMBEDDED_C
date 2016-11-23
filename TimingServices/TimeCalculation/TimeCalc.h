/*
 * TimeCalc.h
 *
 * Created: 11/21/2016 3:14:40 PM
 *  Author: AhmedShaarawy
 */ 


/********************************************************************************************************************
**  >> HOW TO USE THIS TIME SERVICE ?
** 
** (1) You must call StartTimer(ID) at the moment you want to start the counts
** (2) When you want to get time at any moment call GetTimerCounts(....) function in that moment
** (3) You can after that stop timer by calling StopTimer(void) function or leave timer running to get another counts
** 
**  >> HOW TO CALCULATE TIME FROM GetTimerCounts(...) FUNCTION ?
** 
** (1) Get counts function will get two values turns and capture.
**		turns is the number of times that timer over flowed, and capture is the value of the timer register itself.
** (2) The total counts is calculated as TotalCounts(between StartTimer() and GetTimerCounts() )= (turns*TimerRegisterBitsSize)+capture.
** (3) The Time is calculated as TotalTime(between StartTimer() and GetTimerCounts() )= TotalCounts*(TimerPrescale/F_CPU),
**		if there is no Prescale then TimerPrescale equal to one.
**
**  >> HOW TO CALCULATE THE DUTY CYCLE OF INCOMING PULSE-SIGNAL IN_PERCENTAGE ?
**
** (1) You don't need to calculate TotalTime, just calculate the TotalCounts of on-period and the TotalCounts of signal total cycle.
** (2) Multiply the TotalCounts of on-period by 100, then divide the result by the TotalCounts of signal total cycle,
**		, you will get the duty cycle in percentage.
**
**  >> HOW TO CALCULATE A FUNCTION'S TIME ?
**
** (1) You mast call StartTimer(ID) function immediatly befor the function you want to calculate it's time.
** (2) After the desired function you must call GetTimerCounts(...) function immediatly to get the counts.
** (3) Use the counts to calculate function time from our equation explained above.
** (4) Call StopTimer() if you done.
*/



#ifndef TIMECALC_H_
#define TIMECALC_H_
#include "FunctionsTools.h"
#include "atmega32_TIMER0.h"
#include "atmega32_TIMER1.h"
#include "atmega32_TIMER2.h"
// timers IDs
#define TC0ID	0x00
#define TC1ID	0x01
#define TC2ID	0x02
// 

/************************************************************************************
** TIMER0 COUPLING
** You must adapt this function to your Timer0 driver
*/
#define TC0_DeclareTimerObject()			sTIMER0	tc0
#define TC0_DisableOutPin()					tc0.OC0PinMode= TC0_OC0_DISABLE
#define TC0_SetTimerNormalMode()			tc0.Mode= TC0_NORMAL_MODE
#define TC0_EnableOVFInt()					tc0.PrescaleClk= TC0_NO_CLKPRESCALE
#define TC0_Pass_IncremeteFn_ToOVFISR()		tc0.DesiredINT= TC0_OVERFLOW_INT
#define TC0_SetTimerPrescaleClk()			tc0.pf_DoAtOverflow= IncrementFn
#define TC0_CallYourInitFunction()			TC0_Init(&tc0)
#define TC0_StopTimer()						TC0_StopTimer0()
#define TC0_CAPTURE_VALUE					TC0_READ_TC0VALUE
#define TC0_COUNTS_PER_TURN					256		// 8 bit timer size
/*************************************************************************************/


/*************************************************************************************
** TIMER1 COUPLING
** You must adapt this function to your Timer1 driver
*/

#define TC1_DeclareTimerObject()			sTIMER1	tc1
#define TC1_DisableOutPin()					tc1.OC1APinMode= TC1_OC1x_DISABLE;\
											tc1.OC1BPinMode= TC1_OC1x_DISABLE
#define TC1_SetTimerNormalMode()			tc1.Mode= TC1_NORMAL_MODE
#define TC1_EnableOVFInt()					tc1.DesiredINT= TC1_OVERFLOW_1INT
#define TC1_SetTimerPrescaleClk()			tc1.Prescale= TC1_NO_CLKPRESCALE
#define TC1_Pass_IncremeteFn_ToOVFISR()		tc1.pf_DoAtOverflow= IncrementFn
#define TC1_CallYourInitFunction()			TC1_Init(&tc1)
#define TC1_StopTimer()						TC1_StopTimer1()
#define TC1_CAPTURE_VALUE					TC1_READ_TC1VALUE
#define TC1_COUNTS_PER_TURN					65536	// 16 bit timer size
/************************************************************************************/


/************************************************************************************
** TIMER2 COUPLING
** You must adapt this function to your Timer2 driver
*/

#define TC2_DeclareTimerObject()			sTIMER2	tc2
#define TC2_DisableOutPin()					tc2.OC2PinMode= TC2_OC2_DISABLE
#define TC2_SetTimerNormalMode()			tc2.Mode= TC2_NORMAL_MODE
#define TC2_EnableOVFInt()					tc2.DesiredINT= TC2_OVERFLOW_INT
#define TC2_SetTimerPrescaleClk()			tc2.Prescale= TC2_NO_CLKPRESCALE
#define TC2_Pass_IncremeteFn_ToOVFISR()		tc2.pf_DoAtOverflow= IncrementFn
#define TC2_CallYourInitFunction()			TC2_Init(&tc2)
#define TC2_StopTimer()						TC2_StopTimer2()
#define TC2_CAPTURE_VALUE					TC2_READ_TC2VALUE
#define TC2_COUNTS_PER_TURN					256		// 8 bit timer size
/***********************************************************************************/


STD_R StartTimer(U8 TimerId);
STD_R GetTimerCounts( U32 *turns, U16 *capture);
STD_R StopTimer(void);
// increment functions
void IncrementFn(void);






#endif /* TIMECALC_H_ */