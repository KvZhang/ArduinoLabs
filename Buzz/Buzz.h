/*
 * Buzz.h
 *
 *  Created on: 2017Äê3ÔÂ26ÈÕ
 *      Author: zhangyu
 */

#ifndef BUZZ_H_
#define BUZZ_H_

#include "Arduino.h"

#define BUZZ_ON 			LOW
#define BUZZ_OFF			HIGH

typedef struct
{
	unsigned int on_time;//ms
	unsigned int off_time;//ms
	unsigned int cycles;//
}STRUCT_BUZZ_CONFIG;

class Buzz {
public:
	Buzz(uint8_t buzzPin=6);
	void set(uint8_t cycles, uint16_t on_time=200, uint16_t off_time=200);
	void handler();
	virtual ~Buzz();
private:
	uint8_t buzzPin;
	uint32_t last_on_time;
	uint32_t last_off_time;
	STRUCT_BUZZ_CONFIG buzz;
};

#endif /* BUZZ_H_ */
