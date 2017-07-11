/*
 * Door.h
 *
 *  Created on: 2017Äê3ÔÂ25ÈÕ
 *      Author: zhangyu
 */

#ifndef DOOR_H_
#define DOOR_H_

#include "Arduino.h"
typedef enum
{
	Door_status_closed,
	Door_status_opened,
	Door_status_open_failed,
	Door_status_close_failed,
}DOOR_STATUS;

typedef enum
{
	Open_door,
	Close_door,
}DOOR_ACTION;

typedef enum
{
	Door_out_of_position,
	Door_in_position,
}DOOR_POSITION;

typedef enum
{
	Door_unlocked,
	Door_locked,
}DOOR_LOCK_STATUS;

class Door {
public:
	Door(uint8_t powerPin,uint8_t detectDoorPin,uint8_t detectLockPin);
	void handler();
	void openDoor(uint16_t open_time_s=3,uint16_t alert_time_s=5);
	uint8_t Read_door_status();
	virtual ~Door();
private:
	uint8_t powerPin;
	uint8_t detectDoorPin;
	uint8_t detectLockPin;
	uint8_t status;
	uint32_t open_moment_ms;
	uint32_t close_moment_ms;
	uint32_t open_time_s;
	uint32_t alert_time_s;
};

#endif /* DOOR_H_ */
