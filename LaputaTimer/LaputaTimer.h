/*
 * LaputaTimer.h
 *
 *  Created on: 2015Äê11ÔÂ3ÈÕ
 *      Author: zhangyu
 *      if you want to transplant to other platform, just need to
 *      check typedef, include and modify getSysTimestamp()
 */

#ifndef LAPUTATIMER_H_
#define LAPUTATIMER_H_
#include "Arduino.h"
typedef unsigned char BYTE;
typedef unsigned int  WORD;
typedef unsigned long DWORD;
typedef void (*_Pfn)(void);

#define MAX_SYS_TIMER (5)//modify the numbers for your application

typedef struct _TIMER{
	BYTE Active;
	BYTE type;//0 non repeat, 1 repeat
	_Pfn pTimerFunc;
	DWORD Elapse;
	DWORD StartTime;
}SYS_TIMER;

class LaputaTimer {
public:
	LaputaTimer();
	SYS_TIMER SysTimer[MAX_SYS_TIMER];
	void processTimer();//need to be put on in a loop, main loop is good enough
	BYTE SetTimer(DWORD Elapse, _Pfn pTimerFunc, BYTE repeatType);
	BYTE SetTimer(DWORD Elapse, _Pfn pTimerFunc);
	void KillTimer(BYTE *pTimerID);
	void RestartTimer(BYTE *pTimerID);
	virtual ~LaputaTimer();
	private:
	DWORD getSysTimestamp();//get time stamp in millisecond
};

#endif /* LAPUTATIMER_H_ */
