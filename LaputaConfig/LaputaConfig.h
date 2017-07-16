/*
 * LaputaConfig.h
 *
 *  Created on: 2017Äê5ÔÂ14ÈÕ
 *      Author: zhangyu
 */

#ifndef LAPUTACONFIG_H_
#define LAPUTACONFIG_H_

#include "Arduino.h"
#include "EEPROM.h"

typedef struct
{
	uint8_t room_addr;
	uint8_t me_addr;
	uint8_t sys_rsv[12];
	uint16_t count;
	uint8_t user_data[14];
	uint16_t checksum;
}EEPROM_STRUCT;

#define EEPROM_ADDR (0)

class LaputaConfig
{
public:
	LaputaConfig();
	virtual ~LaputaConfig();
	EEPROM_STRUCT context;
	bool load_config();
	void save_config();
private:
	bool calc_chksum();
};

#endif /* LAPUTACONFIG_H_ */
