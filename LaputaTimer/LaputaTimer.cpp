/*
 * LaputaTimer.cpp
 *
 *  Created on: 2015Äê11ÔÂ3ÈÕ
 *      Author: zhangyu
 *      Need put processTimer() in loop(){}
 */

#include "LaputaTimer.h"
LaputaTimer::LaputaTimer() {
	// TODO Auto-generated constructor stub
	for (unsigned char i = 0; i < MAX_SYS_TIMER; i++) {
		this->SysTimer[i].Active = 0;
		this->SysTimer[i].type = 0;
		this->SysTimer[i].pTimerFunc = 0;
		this->SysTimer[i].Elapse = 0;
		this->SysTimer[i].StartTime = 0;
	}
}

LaputaTimer::~LaputaTimer() {
	// TODO Auto-generated destructor stub
}
void LaputaTimer::processTimer() {
	DWORD currentTimestamp = this->getSysTimestamp();
	for (unsigned char i = 0; i < MAX_SYS_TIMER; i++) {
		if (this->SysTimer[i].Active) {
			if ((currentTimestamp - this->SysTimer[i].StartTime)
					>= this->SysTimer[i].Elapse) {

				if (this->SysTimer[i].pTimerFunc != NULL) {
					if (this->SysTimer[i].type == 1) {
						this->SysTimer[i].StartTime = currentTimestamp;
					} else {
						this->SysTimer[i].Active = 0;
					}
					this->SysTimer[i].pTimerFunc();
				} else {
					this->SysTimer[i].Active = 0;
				}

			}
		}
	}
}
BYTE LaputaTimer::SetTimer(DWORD Elapse, _Pfn pTimerFunc) {
	BYTE i;

	if (Elapse == 0) {
		if (pTimerFunc != 0) {
			pTimerFunc();
		}
	} else {
		for (i = 0; i < MAX_SYS_TIMER; i++) {
			if (this->SysTimer[i].Active == 0) {
				this->SysTimer[i].Active = 1;
				this->SysTimer[i].type = 0;
				this->SysTimer[i].pTimerFunc = pTimerFunc;
				this->SysTimer[i].Elapse = Elapse;
				this->SysTimer[i].StartTime = this->getSysTimestamp();
				return i + 1;
			}
		}
	}
	return 0;
}
BYTE LaputaTimer::SetTimer(DWORD Elapse, _Pfn pTimerFunc, BYTE repeatType) {
	BYTE temp = this->SetTimer(Elapse, pTimerFunc);
	if (temp != 0) {
		this->SysTimer[temp - 1].type = repeatType;
	}
	return temp;
}
//-------------------------------- RestartTimer --------------------------------------
void LaputaTimer::RestartTimer(BYTE *pTimerID) {
	if (*pTimerID <= 0 || *pTimerID > MAX_SYS_TIMER)
		return;

	if (this->SysTimer[*pTimerID - 1].Active == 0)
		return;

	this->SysTimer[*pTimerID - 1].StartTime = this->getSysTimestamp();
}

//-------------------------------- KillTimer --------------------------------------
void LaputaTimer::KillTimer(BYTE *pTimerID) {
	if (*pTimerID <= 0 || *pTimerID > MAX_SYS_TIMER)
		return;

	this->SysTimer[*pTimerID - 1].Active = 0;
	this->SysTimer[*pTimerID - 1].type = 0;

	*pTimerID = 0;
}
DWORD LaputaTimer::getSysTimestamp() {
	return millis();
}
