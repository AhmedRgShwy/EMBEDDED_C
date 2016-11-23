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
** (2) After calling the desired function you must call GetTimerCounts(...) function immediatly to get the counts.
** (3) Use the counts to calculate function time from our equation explained above.
** (4) Call StopTimer() if you done.
*/