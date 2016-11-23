/*
 * Timers_TimeCalc.c
 *
 * Created: 11/21/2016 3:13:10 PM
 *  Author: AhmedShaarawy
 */ 


#include "TimeCalc.h"

int main(void)
{
	
	
	U32 i, turns1, turns2 ;
	U16 capture1, capture2;
	
	StartTimer(0);
	for (i=0;i<5000;i++);
	
	GetTimerCounts(&turns1,&capture1);
	
	for (i=0;i<7000;i++);
	
	GetTimerCounts(&turns2,&capture2);
	
	StopTimer();
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}