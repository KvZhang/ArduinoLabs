/*
 * Buzz.cpp
 *
 *  Created on: 2017Äê3ÔÂ26ÈÕ
 *      Author: zhangyu
 */

#include "Buzz.h"

Buzz::Buzz(uint8_t buzzPin) {
	// TODO Auto-generated constructor stub
	this->buzzPin=buzzPin;
	pinMode(this->buzzPin,OUTPUT);
	digitalWrite(buzzPin,BUZZ_OFF);
	this->last_off_time=0;
	this->last_on_time=0;
	this->buzz.cycles=0;
	this->buzz.off_time=200;
	this->buzz.on_time=200;
}

void Buzz::set(uint8_t cycles, uint16_t on_time, uint16_t off_time)
{
	this->buzz.cycles=cycles;
	this->buzz.off_time=off_time;
	this->buzz.on_time=on_time;
}
void Buzz::handler()
{
	unsigned char state=digitalRead(this->buzzPin);//1: off;0: on
	if(this->buzz.cycles)
	{
		if(state)
		{
			if(this->last_off_time)
			{
			if(millis()-this->last_off_time>this->buzz.off_time)
			{
				if(--this->buzz.cycles)
				{
					digitalWrite(this->buzzPin,BUZZ_ON);
					this->last_on_time=millis();
				}
				else
				{
					this->last_off_time=0;
				}
			}
			}
			else
			{
				digitalWrite(this->buzzPin,BUZZ_ON);
				this->last_on_time=millis();
			}
		}
		else
		{
			if(millis()-this->last_on_time>this->buzz.on_time)
			{
				digitalWrite(this->buzzPin,BUZZ_OFF);
				this->last_off_time=millis();
			}
		}
	}
	else if(state==0)
	{
		digitalWrite(this->buzzPin,BUZZ_OFF);
		this->last_off_time=0;
	}
}

Buzz::~Buzz() {
	// TODO Auto-generated destructor stub
}

