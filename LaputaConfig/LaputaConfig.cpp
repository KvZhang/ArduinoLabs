/*
 * LaputaConfig.cpp
 *
 *  Created on: 2017Äê5ÔÂ14ÈÕ
 *      Author: zhangyu
 */

#include "LaputaConfig.h"

LaputaConfig::LaputaConfig()
{
	// TODO Auto-generated constructor stub
	memset(&this->context,0,sizeof(EEPROM_STRUCT));
}

bool LaputaConfig::load_config()
{
	uint8_t * ptr=(uint8_t *)&this->context;
	for(uint8_t i=0;i<sizeof(EEPROM_STRUCT);i++)
	{
		*(ptr+i)=EEPROM.read(EEPROM_ADDR+i);
	}
	if(!this->calc_chksum())
	{
		memset(&this->context,0,sizeof(EEPROM_STRUCT));
		for(uint8_t i=0;i<sizeof(EEPROM_STRUCT);i++)
		{
			EEPROM.update(EEPROM_ADDR+i, 0xff);
		}
		return 1;
	}
	++this->context.count;
	this->save_config();
	if(this->context.count>100)
	{
		return 1;
	}

	return 0;
}
void LaputaConfig::save_config()
{
	uint8_t * ptr=(uint8_t *)&this->context;
	this->context.checksum=0;
	for(uint8_t i=0;i<sizeof(EEPROM_STRUCT)-2;i++)
	{
		EEPROM.update(EEPROM_ADDR+i, *(ptr+i));
		this->context.checksum+=*(ptr+i);
	}
	EEPROM.update(EEPROM_ADDR+sizeof(EEPROM_STRUCT)-2, *(ptr+sizeof(EEPROM_STRUCT)-2));
	EEPROM.update(EEPROM_ADDR+sizeof(EEPROM_STRUCT)-1, *(ptr+sizeof(EEPROM_STRUCT)-1));
}
bool LaputaConfig::calc_chksum()
{
	uint8_t * ptr=(uint8_t *)&this->context;
	if(this->context.checksum==0)
	{
		return 0;
	}
	uint16_t temp=0;
	for(uint8_t i=0;i<sizeof(EEPROM_STRUCT)-2;i++)
	{
		temp+=*(ptr+i);
	}
	if(temp==this->context.checksum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
LaputaConfig::~LaputaConfig()
{
	// TODO Auto-generated destructor stub

}

