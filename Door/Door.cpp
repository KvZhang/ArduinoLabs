/*
 * Door.cpp
 *
 *  Created on: 2017Äê3ÔÂ25ÈÕ
 *      Author: zhangyu
 */

#include "Door.h"

Door::Door(uint8_t powerPin,uint8_t detectDoorPin,uint8_t detectLockPin) {
	// TODO Auto-generated constructor stub
	this->detectDoorPin=detectDoorPin;
	this->detectLockPin=detectLockPin;
	this->powerPin=powerPin;
	this->open_moment_ms=0;
	this->close_moment_ms=0;
	this->open_time_s=0;
	this->alert_time_s=0;
	this->status=Door_status_closed;

	pinMode(this->powerPin,OUTPUT);
	pinMode(this->detectDoorPin,INPUT_PULLUP);
	pinMode(this->detectLockPin,INPUT_PULLUP);
	digitalWrite(this->powerPin,Close_door);
}
void Door::openDoor(uint16_t open_time_s=3,uint16_t alert_time_s=5)
{
	if(open_time_s>0)
	{
		digitalWrite(powerPin,Open_door);
		this->open_time_s=open_time_s;
		this->alert_time_s=alert_time_s;
		this->open_moment_ms=millis();
	}
	else
	{
		digitalWrite(powerPin,Close_door);
		this->open_time_s=0;
	}
}

void Door::handler()
{
	//door should be opened
	if(this->open_moment_ms)
	{
		if((millis()-this->open_moment_ms)<500)// door respond time 500ms
		{

		}
		else if((millis()-this->open_moment_ms)<(this->open_time_s*1000))
		{
			if(digitalRead(this->detectDoorPin)==Door_out_of_position)//door is removed
			{
				this->status=Door_status_opened;
			}
			else if(digitalRead(this->detectLockPin)==Door_unlocked)//door unlocked but need push, that is OK
			{
				this->status=Door_status_opened;
			}
			else
			{
				this->status=Door_status_open_failed;
			}
		}
		else
		{
			this->open_moment_ms=0;
			digitalWrite(powerPin,Close_door);
			this->close_moment_ms=millis();
		}
	}
	//door should be closed
	else
	{
		if(digitalRead(this->detectLockPin)==Door_locked && digitalRead(this->detectDoorPin)==Door_in_position)
		{
			this->status=Door_status_closed;
		}
		else if(millis()-this->close_moment_ms>this->alert_time_s*1000)// over 5 second but the door is still opened, warning
		{
			this->status=Door_status_close_failed;
		}
		else
		{
			this->status=Door_status_opened;
		}
	}
}

uint8_t Door::Read_door_status()
{
	return this->status;
}

Door::~Door() {
	// TODO Auto-generated destructor stub

}

